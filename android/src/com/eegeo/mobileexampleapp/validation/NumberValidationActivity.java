package com.eegeo.mobileexampleapp.validation;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.drawable.ColorDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.provider.Settings;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v4.content.ContextCompat;
import android.telephony.TelephonyManager;
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
import com.netsoltech.jcgroup.mobileexampleapp.R;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

import static com.eegeo.mobileexampleapp.validation.ValidationConstants.KEY_IS_VALIDATED;
import static com.eegeo.mobileexampleapp.validation.ValidationConstants.VALIDATION_BASE_URL;

/**
 * Created by najhi on 23/05/2018.
 */

public class NumberValidationActivity extends FragmentActivity  implements INumberEnteredCallback, IValidationCodeScreenCallback, IResponseScreenCallback
{
    private static final int PERMISSION_READ_PHONE_STATE = 101;
    private ValidationPersistentState m_persistentState;
    private int m_subscreensCount = 0;
    private Handler m_handlerLooper = new Handler(Looper.getMainLooper());
    private Dialog m_progressDialog;
    private boolean m_isLoading;
    private String m_deviceId;

    public boolean m_isTestFlight = true;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        m_persistentState = new ValidationPersistentState(this, 0);

        if(m_persistentState.containsKey(KEY_IS_VALIDATED) && m_persistentState.getBoolean(KEY_IS_VALIDATED))
        {
            finish();
            startActivity(new Intent(this, BackgroundThreadActivity.class));
        }
        else
        {
            initUi();
            initVolley();
            loadDeviceId();
        }
    }

    private void initUi()
    {
        setContentView(R.layout.validation_layout);
        addEnterPhoneFragment();
    }

    private void initVolley()
    {
        VolleyLog.setTag("Volley");
        VolleyLog.DEBUG = true;
    }

    @SuppressLint("MissingPermission")
    private void loadDeviceId()
    {
        m_deviceId = Settings.Secure.getString(getContentResolver(), Settings.Secure.ANDROID_ID);

        if(m_deviceId==null || m_deviceId.equals("")) {
            if (hasPhoneStateReadPermissions())
            {
                TelephonyManager tManager = (TelephonyManager)getSystemService(Context.TELEPHONY_SERVICE);
                m_deviceId = tManager.getDeviceId();
            }
        }
        Log.v("Validation", "Device ID = " + m_deviceId);
    }

    private void addEnterPhoneFragment()
    {
        EnterNumberFragment enterNumberFragment = new EnterNumberFragment();
        enterNumberFragment.init(this);
        replaceFragment(enterNumberFragment, "EnterNumberFragment", false, false);
    }

    private void addValidationCodeFragment(String preNumber, String mobileNumber)
    {
        EnterValidationCodeFragment enterValidationCodeFragment = new EnterValidationCodeFragment();
        enterValidationCodeFragment.init(preNumber, mobileNumber, this);
        replaceFragment(enterValidationCodeFragment, "EnterValidationCodeFragment", true, true);
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
    public void onNumberEntered(String preNumber, String mobileNumber, IOnErrorResponse onErrorResponse)
    {
        requestVerificationCode(preNumber, mobileNumber, onErrorResponse);
    }

    private void requestVerificationCode(String preNumber, String mobileNumber, IOnErrorResponse onErrorResponse)
    {
        requestVerificationCode(preNumber, mobileNumber, onErrorResponse, false, null);
    }

    private void requestVerificationCode(String preNumber, String mobileNumber, boolean isResend, IOnResendResponseReceivedCallback onResendResponseReceived)
    {
        requestVerificationCode(preNumber, mobileNumber, null, isResend, onResendResponseReceived);
    }

    private void requestVerificationCode(final String preNumber, final String mobileNumber, final IOnErrorResponse onErrorResponse, final boolean isResend, final IOnResendResponseReceivedCallback onResendResponseReceived)
    {
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        String url = VALIDATION_BASE_URL + "app/system/sendCode";

        Map<String, String>  headers = new HashMap<String, String>();
        headers.put("content-type", "application/json");

        Map<String, String>  params = new HashMap<String, String>();
        params.put("preNo", preNumber);
        params.put("mobileNo", mobileNumber);

        onLoadingStarted();

        CustomRequest request = new CustomRequest(
                Request.Method.POST,
                url,
                headers,
                params,
                new Response.Listener<JSONObject>()
                {
                    @Override
                    public void onResponse(JSONObject response)
                    {
                        Log.i("Volley", "Response:" + response.toString());
                        handleNumberResponse(response, preNumber, mobileNumber, onErrorResponse, isResend, onResendResponseReceived);
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
                            Log.i("Volley", "Response error:" + error.getMessage());
                        }
                        showNetworkErrorDialog();
                        onLoadingFinished();
                    }
                });

        try {
            Log.i("Volley", "Request body: " + new String(request.getBody()));
        } catch (AuthFailureError authFailureError) {
            authFailureError.printStackTrace();
        }
        requestQueue.add(request);
    }

    private void handleNumberResponse(JSONObject response, String preNumber, String mobileNumber, IOnErrorResponse onErrorResponse, boolean isResend, IOnResendResponseReceivedCallback onResendResponseReceivedCallback)
    {
        if(response.has("code"))
        {
            int code = response.optInt("code");
            if(code == 0)
            {
                if(isResend)
                {
                    onResendResponseReceivedCallback.onResendResponseReceived();
                }
                else
                {
                    addValidationCodeFragment(preNumber, mobileNumber);
                }
            }
            else
            {
                if(!isResend)
                {
                    String error = response.optString("errmsg");
                    onErrorResponse.onError(error);
                }
            }
        }
        else
        {
            if(!isResend)
            {
                String error = "Internal Server Error";
                onErrorResponse.onError(error);
            }
        }
    }

    @Override
    public void onValidationCodeEntered(String m_preNumber, String m_mobileNumber, int validationCode, final IOnErrorResponse onErrorResponse)
    {
        RequestQueue requestQueue = Volley.newRequestQueue(this);

        Map<String, String>  headers = new HashMap<>();
        headers.put("content-type", "application/json");

        String url = VALIDATION_BASE_URL + "oa/codeEmployeeLogin";
        Map<String, String>  params = new HashMap<>();
        params.put("code", validationCode + "");
        params.put("pre", m_preNumber);
        params.put("mobi", m_mobileNumber);

        onLoadingStarted();

        CustomRequest request = new CustomRequest(
                Request.Method.POST,
                url,
                headers,
                params,
                new Response.Listener<JSONObject>()
                {
                    @Override
                    public void onResponse(JSONObject response)
                    {
                        Log.e("Volley", "Response:" + response.toString());
                        handleVerifyResponse(response, onErrorResponse);
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
                            Log.e("Volley", "Response error:" + error.getMessage());
                        }
                        showNetworkErrorDialog();
                        onLoadingFinished();
                    }
                });

        try {
            Log.i("Volley", "Request body: " + new String(request.getBody()));
        } catch (AuthFailureError authFailureError) {
            authFailureError.printStackTrace();
        }
        requestQueue.add(request);
    }

    private void handleVerifyResponse(JSONObject response, IOnErrorResponse onErrorResponse)
    {

        if(response.has("code"))
        {
            int code = response.optInt("code");
            if(code == 0)
            {
                m_persistentState.setBoolean(KEY_IS_VALIDATED, true);
                addResponseStatusFragment(true, getString(R.string.validation_success_text));
            }
            else
            {
                String error = response.optString("errmsg");
                onErrorResponse.onError(error);
            }
        }
        else
        {
            String error = "Internal Server Error";
            onErrorResponse.onError(error);
        }
    }

    @Override
    public void onResendCodeRequest(String preNumber, String mobileNumber, IOnResendResponseReceivedCallback onResendResponseReceived)
    {
        requestVerificationCode(preNumber, mobileNumber, true, onResendResponseReceived);
    }

    @Override
    public void onValidationCodeExpired()
    {
        onBackPressed();
    }

    @Override
    public void onDoneButtonSelected(boolean isSuccess)
    {
        if(isSuccess)
        {
            finish();
            startActivity(new Intent(this, BackgroundThreadActivity.class));
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
            startActivity(new Intent(this, BackgroundThreadActivity.class));
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

    private void showDebugPinDialog(String pin)
    {
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(new ContextThemeWrapper(this, R.style.AlertDialogCustom));
        alertDialogBuilder.setTitle("Success")
                .setMessage("Your pin is : " + pin)
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
                m_progressDialog = new Dialog(NumberValidationActivity.this);
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

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
    {
        if(requestCode == PERMISSION_READ_PHONE_STATE)
        {
            if(grantResults.length == 1 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
            {
                loadDeviceId();
            }
            else
            {
                showPermissionRequiredDialog(this);
            }
        }
    }

    public boolean hasPhoneStateReadPermissions()
    {
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.READ_PHONE_STATE) == PackageManager.PERMISSION_GRANTED)
        {
            return true;
        }
        else
        {
            ActivityCompat.requestPermissions(this,
                    new String[] { Manifest.permission.READ_PHONE_STATE},
                    PERMISSION_READ_PHONE_STATE);
        }
        return false;
    }

    public void startAppSettings(final Context context)
    {
        if(context == null)
        {
            return;
        }
        final Intent i = new Intent();
        i.setAction(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
        i.addCategory(Intent.CATEGORY_DEFAULT);
        i.setData(Uri.parse("package:" + context.getPackageName()));
        i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        i.addFlags(Intent.FLAG_ACTIVITY_NO_HISTORY);
        i.addFlags(Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS);
        context.startActivity(i);
    }

    private void showPermissionRequiredDialog(final Activity context)
    {
        DialogInterface.OnClickListener dialogClickListener = new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which)
            {
                dialog.dismiss();
                switch(which)
                {
                    case DialogInterface.BUTTON_POSITIVE:
                        if (ActivityCompat.shouldShowRequestPermissionRationale(context, Manifest.permission.READ_PHONE_STATE))
                        {
                            // Checking Permissions again
                            hasPhoneStateReadPermissions();
                        }
                        else
                        {
                            // Open App Settings Page
                            startAppSettings(context);
                        }
                        break;

                    case DialogInterface.BUTTON_NEGATIVE:
                        finish();
                        break;
                }
            }
        };

        AlertDialog.Builder builder = new AlertDialog.Builder(new ContextThemeWrapper(this, R.style.AlertDialogCustom));
        builder.setMessage(context.getResources().getString(R.string.required_read_device_state_permission_msg))
                .setPositiveButton(context.getResources().getString(R.string.ok_text), dialogClickListener)
                .setNegativeButton(context.getResources().getString(R.string.cancel_text), dialogClickListener)
                .setCancelable(false)
                .show();
    }
}
