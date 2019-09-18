package com.eegeo.mobileexampleapp.validation;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.drawable.ColorDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.util.Base64;
import android.util.Log;
import android.view.ContextThemeWrapper;
import android.view.Window;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.Volley;
import com.eegeo.mobileexampleapp.BackgroundThreadActivity;
import com.eegeo.mobileexampleapp.R;


import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

import static com.eegeo.mobileexampleapp.validation.ValidationConstants.KEY_IS_VALIDATED;
import static com.eegeo.mobileexampleapp.validation.ValidationConstants.VALIDATION_BASE_URL;

/**
 * Created by najhi on 23/05/2018.
 */

public class ValidationActivity extends FragmentActivity  implements ICredentialsEnteredCallback, IResponseScreenCallback
{
    private ValidationPersistentState m_persistentState;
    private int m_subscreensCount = 0;
    private Handler m_handlerLooper = new Handler(Looper.getMainLooper());
    private Dialog m_progressDialog;
    private boolean m_isLoading;
    private Uri m_deepLinkUrlData;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        m_persistentState = new ValidationPersistentState(this, 0);

        Intent intent = getIntent();
        if (intent != null && intent.getData() != null)
        {
            m_deepLinkUrlData = intent.getData();
        }

        if(m_persistentState.containsKey(KEY_IS_VALIDATED) && m_persistentState.getBoolean(KEY_IS_VALIDATED))
        {
            finish();
            startMainActivity();
        }
        else
        {
            initUi();
            initVolley();
        }
    }

    @Override
    public void onNewIntent(Intent intent)
    {
        m_deepLinkUrlData = intent.getData();
    }

    private void initUi()
    {
        setContentView(R.layout.validation_layout);
        addEnterCredentialsFragment();
    }

    private void initVolley()
    {
        VolleyLog.setTag("Volley");
        VolleyLog.DEBUG = true;
    }

    private void addEnterCredentialsFragment()
    {
        EnterCredentialsFragment enterCredentialsFragment = new EnterCredentialsFragment();
        enterCredentialsFragment.init(this);
        replaceFragment(enterCredentialsFragment, "EnterCredentialsFragment", false, false);
    }

    private void addResponseStatusFragment(boolean isSuccess, String message)
    {
        ResponseStatusFragment fragment = new ResponseStatusFragment();
        fragment.init(isSuccess, message, this);
        replaceFragment(fragment, "ResponseStatusFragment", true, true);
    }

    public void replaceFragment(final Fragment fragment, final String tag, boolean addToBackStack, boolean animate)
    {
        FragmentTransaction fragmentTransaction = getSupportFragmentManager()
                .beginTransaction();
        if(animate)
        {
            fragmentTransaction.setCustomAnimations(
                    R.anim.push_right_in,
                    R.anim.push_right_out,
                    R.anim.push_left_in,
                    R.anim.push_left_out);
        }
        else
        {
            fragmentTransaction.setCustomAnimations(
                    0,
                    0,
                    R.anim.push_left_in,
                    R.anim.push_left_out);
        }

        fragmentTransaction.replace(R.id.content_frame, fragment, tag);

        if(addToBackStack)
        {
            fragmentTransaction.addToBackStack(null);
        }

        fragmentTransaction.commit();

        m_subscreensCount++;
    }

    @Override
    public void onCredentialsEntered(String username, String password, IOnErrorResponse onErrorResponse)
    {
        //validateUserCredentials(username, password, onErrorResponse);
        handleCredentialsResponse();
    }

    private void validateUserCredentials(final String username, final String password, final IOnErrorResponse onErrorResponse)
    {
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        String url = VALIDATION_BASE_URL + "oauth/token?username="+username+"&password="+password+"&grant_type=password";

        Map<String, String>  headers = new HashMap<String, String>();
        headers.put("content-type", "application/json");
        headers.put("Authorization", getAuthorizationHeader());

        onLoadingStarted();

        CustomRequest request = new CustomRequest(
                Request.Method.POST,
                url,
                headers,
                null,
                new Response.Listener<JSONObject>()
                {
                    @Override
                    public void onResponse(JSONObject response)
                    {
                        Log.i("Volley", "Response:" + response.toString());
                        //handleCredentialsResponse(response, onErrorResponse);
                        onLoadingFinished();
                    }
                },
                new Response.ErrorListener()
                {
                    @Override
                    public void onErrorResponse(VolleyError error)
                    {
                        if(error != null)
                        {
                            if(error.networkResponse!=null)
                            {
                                byte[] errorBytes = error.networkResponse.data;
                                if(errorBytes.length > 0)
                                {
                                    String errorMessage = new String(errorBytes);
                                    Log.i("Volley", "Response error:" + errorMessage);
                                    try {
                                        JSONObject jsonObject = new JSONObject(errorMessage);
                                        if(jsonObject.has("error_description"))
                                        {
                                            String errorDetailedMsg = jsonObject.getString("error_description");
                                            onErrorResponse.onError(errorDetailedMsg);
                                        }
                                        else
                                        {
                                            showNetworkErrorDialog();
                                        }
                                    } catch (JSONException e) {
                                        e.printStackTrace();
                                        showNetworkErrorDialog();
                                    }

                                }
                            }
                            else
                            {
                                showNetworkErrorDialog();
                            }
                        }
                        else
                        {
                            showNetworkErrorDialog();
                        }

                        onLoadingFinished();
                    }
                });

        requestQueue.add(request);
    }

    private void handleCredentialsResponse()
    {
            m_persistentState.setBoolean(KEY_IS_VALIDATED, true);
            addResponseStatusFragment(true, getString(R.string.validation_success_text));

    }

    @Override
    public void onDoneButtonSelected(boolean isSuccess)
    {
        if(isSuccess)
        {
            finish();
            startMainActivity();
        }
        else
        {
            onBackPressed();
        }
    }

    @Override
    public void onBackPressed()
    {
        if(m_persistentState.containsKey(KEY_IS_VALIDATED) && m_persistentState.getBoolean(KEY_IS_VALIDATED))
        {
            finish();
            startMainActivity();
            return;
        }

        if(m_subscreensCount > 2)
        {
            getSupportFragmentManager().popBackStack(null, FragmentManager.POP_BACK_STACK_INCLUSIVE);
            m_subscreensCount = 1;
        }
        else
        {
            super.onBackPressed();
            m_subscreensCount--;
        }
    }

    private void showNetworkErrorDialog()
    {
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(new ContextThemeWrapper(this, R.style.AlertDialogCustom));
        alertDialogBuilder.setTitle("Error")
                .setMessage("Please make sure you are connected to the internet")
                .setCancelable(false)
                .setPositiveButton("Ok", new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                });
        AlertDialog alert = alertDialogBuilder.create();
        alert.show();
    }

    public void onLoadingStarted() {

        if (m_progressDialog != null && m_progressDialog.isShowing())
        {
            return;
        }

        m_handlerLooper.post(new Runnable()
        {
            @Override
            public void run()
            {
                m_progressDialog = new Dialog(ValidationActivity.this);
                m_progressDialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
                m_progressDialog.getWindow().setBackgroundDrawable(new ColorDrawable(android.graphics.Color.TRANSPARENT));
                m_progressDialog.setContentView(R.layout.progress);
                m_progressDialog.setCancelable(false);
                m_progressDialog.show();
            }
        });

        m_isLoading = true;
    }

    public void onLoadingFinished()
    {
        if (m_progressDialog != null && m_progressDialog.isShowing())
        {
            m_handlerLooper.post(new Runnable()
            {
                @Override
                public void run()
                {
                    m_progressDialog.dismiss();
                }
            });
        }

        m_isLoading = false;
    }

    public String getAuthorizationHeader()
    {
        String credentials = getString(R.string.validation_username)+":"+getString(R.string.validation_password);
        String auth = "Basic "
                + Base64.encodeToString(credentials.getBytes(),
                Base64.NO_WRAP);
        return auth;
    }

    private void startMainActivity()
    {
        Intent intent = new Intent(this, BackgroundThreadActivity.class);
        if(m_deepLinkUrlData != null)
        {
            intent.setData(m_deepLinkUrlData);
        }
        startActivity(intent);
    }
}
