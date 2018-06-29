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

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.Volley;
import com.eegeo.mobileexampleapp.BackgroundThreadActivity;
import com.netsoltech.jcgroup.mobileexampleapp.R;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

import static com.eegeo.mobileexampleapp.validation.ValidationConstants.KEY_IS_VALIDATED;
import static com.eegeo.mobileexampleapp.validation.ValidationConstants.VALIDATION_BASE_URL;
import static com.eegeo.mobileexampleapp.validation.ValidationConstants.VALIDATION_STATUS.STATUS_ATTEMPTS_EXCEEDED;
import static com.eegeo.mobileexampleapp.validation.ValidationConstants.VALIDATION_STATUS.STATUS_BLOCKED;
import static com.eegeo.mobileexampleapp.validation.ValidationConstants.VALIDATION_STATUS.STATUS_ERROR;
import static com.eegeo.mobileexampleapp.validation.ValidationConstants.VALIDATION_STATUS.STATUS_EXPIRED;
import static com.eegeo.mobileexampleapp.validation.ValidationConstants.VALIDATION_STATUS.STATUS_IN_PROGRESS;
import static com.eegeo.mobileexampleapp.validation.ValidationConstants.VALIDATION_STATUS.STATUS_VERIFIED;
import static com.eegeo.mobileexampleapp.validation.ValidationConstants.VALIDATION_STATUS.STATUS_WRONG_CODE;

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

    private String m_mockNumberResponse = "{\"code\":200,\"message\":\"Successful request\",\"data\":{\"token\":\"8dfd9453b2e04a75c8540917c8d07387e87d53dee18a13a3ad4c4190aee141c1\",\"status\":\"STATUS_IN_PROGRESS\",\"code\":1}}";
    private String m_mockVerifyResponse = "{\"code\":400,\"message\":\"Your verification code is expired.\",\"data\":{\"status\":\"STATUS_ATTEMPTS_EXCEEDED\",\"code\":-1}}";

    private boolean m_isMockResponse = false;
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
            loadDeviceId();
        }
    }

    private void initUi()
    {
        setContentView(R.layout.validation_layout);
        addEnterPhoneFragment();
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

    private void addValidationCodeFragment(String token, String phoneNumber)
    {
        EnterValidationCodeFragment enterValidationCodeFragment = new EnterValidationCodeFragment();
        enterValidationCodeFragment.init(token, phoneNumber, this);
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
    public void onNumberEntered(String phoneNumber, IOnErrorResponse onErrorResponse)
    {
        requestVerificationCode(phoneNumber, onErrorResponse);
    }

    private void requestVerificationCode(String phoneNumber, IOnErrorResponse onErrorResponse)
    {
        requestVerificationCode(phoneNumber, onErrorResponse, false, null);
    }

    private void requestVerificationCode(String phoneNumber, boolean isResend, IOnResendResponseReceivedCallback onResendResponseReceived)
    {
        requestVerificationCode(phoneNumber, null, isResend, onResendResponseReceived);
    }

    private void requestVerificationCode(final String phoneNumber, final IOnErrorResponse onErrorResponse, final boolean isResend, final IOnResendResponseReceivedCallback onResendResponseReceived)
    {
        RequestQueue requestQueue = Volley.newRequestQueue(this);
        String url = VALIDATION_BASE_URL + "send-sms";
        Map<String, String>  params = new HashMap<String, String>();
        params.put("device_id", m_deviceId);
        params.put("platform", "android");
        params.put("number", phoneNumber);

        onLoadingStarted();

        CustomRequest request = new CustomRequest(
                Request.Method.POST,
                url, params,
                new Response.Listener<JSONObject>()
                {
                    @Override
                    public void onResponse(JSONObject response)
                    {
                        Log.e("response", response.toString());
                        if(m_isMockResponse)
                        {
                            try
                            {
                                response = new JSONObject(m_mockNumberResponse);
                            }
                            catch (JSONException e)
                            {
                                e.printStackTrace();
                            }
                        }

                        handleNumberResponse(response, phoneNumber, onErrorResponse, isResend, onResendResponseReceived);
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
                            Log.e("response error", error.getMessage());
                        }
                        showNetworkErrorDialog();
                        onLoadingFinished();
                    }
                });

        requestQueue.add(request);
    }

    private void handleNumberResponse(JSONObject response, String phoneNumber, IOnErrorResponse onErrorResponse, boolean isResend, IOnResendResponseReceivedCallback onResendResponseReceivedCallback)
    {
        try
        {
            if(response.has("data"))
            {
                JSONObject data = response.getJSONObject("data");
                String status = data.optString("status");
                if(status.equals(STATUS_IN_PROGRESS.value()))
                {
                    String token = data.optString("token");

                    if(isResend)
                    {
                        onResendResponseReceivedCallback.onResendResponseReceived(token);
                    }
                    else
                    {
                        addValidationCodeFragment(token, phoneNumber);
                    }

                    if(m_isTestFlight)
                    {
                        String pin = data.optString("pin");
                        showDebugPinDialog(pin);
                    }
                }
                else if(status.equals(STATUS_VERIFIED.value()))
                {
                    m_persistentState.setBoolean(KEY_IS_VALIDATED, true);
                    addResponseStatusFragment(true, getString(R.string.validation_already_verified));
                }
                else if(status.equals(STATUS_BLOCKED.value()))
                {
                    String error = response.optString("message");
                    addResponseStatusFragment(false, error);
                }
                else if(status.equals(STATUS_ERROR.value()))
                {
                    String error = response.optString("message");
                    onErrorResponse.onError(error);
                }
            }
            else
            {
                if(!isResend)
                {
                    String error = response.optString("message");
                    onErrorResponse.onError(error);
                }
            }
        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public void onValidationCodeEntered(int validationCode, String token, final IOnErrorResponse onErrorResponse)
    {
        RequestQueue requestQueue = Volley.newRequestQueue(this);

        String url = VALIDATION_BASE_URL + "verify";
        Map<String, String>  params = new HashMap<String, String>();
        params.put("code", validationCode + "");
        params.put("token", token);

        onLoadingStarted();

        CustomRequest request = new CustomRequest(
                Request.Method.POST,
                url, params,
                new Response.Listener<JSONObject>()
                {
                    @Override
                    public void onResponse(JSONObject response)
                    {
                        Log.e("response", response.toString());
                        if(m_isMockResponse)
                        {
                            try
                            {
                                response = new JSONObject(m_mockVerifyResponse);
                            }
                            catch (JSONException e)
                            {
                                e.printStackTrace();
                            }
                        }
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
                            Log.e("response error", error.getMessage());
                        }
                        showNetworkErrorDialog();
                        onLoadingFinished();
                    }
                });

        requestQueue.add(request);
    }

    private void handleVerifyResponse(JSONObject response, IOnErrorResponse onErrorResponse)
    {
        try
        {
            if(response.has("data"))
            {
                JSONObject data = response.getJSONObject("data");
                String status = data.optString("status");
                if(status.equals(STATUS_VERIFIED.value()))
                {
                    m_persistentState.setBoolean(KEY_IS_VALIDATED, true);
                    addResponseStatusFragment(true, getString(R.string.validation_success_text));
                }
                else if(status.equals(STATUS_WRONG_CODE.value()))
                {
                    String error = response.optString("message");
                    onErrorResponse.onError(error.length() > 0 ? error : "Incorrect PIN!");
                }
                else if(status.equals(STATUS_EXPIRED.value()))
                {
                    String error = response.optString("message");
                    onErrorResponse.onError(error.length() > 0 ? error : "Your PIN has been Expired!");
                }
                else if(status.equals(STATUS_ATTEMPTS_EXCEEDED.value()))
                {
                    String error = response.optString("message");
                    addResponseStatusFragment(false, error);
                }
            }
        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public void onResendCodeRequest(String phoneNumber, IOnResendResponseReceivedCallback onResendResponseReceived)
    {
        requestVerificationCode(phoneNumber, true, onResendResponseReceived);
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
