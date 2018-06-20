package com.eegeo.mobileexampleapp.validation;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.ContextThemeWrapper;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import com.netsoltech.jcgroup.mobileexampleapp.R;

import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by najhiullah on 13/03/2018.
 */

public class EnterValidationCodeFragment extends Fragment implements View.OnClickListener, TextWatcher, IOnErrorResponse, IOnResendResponseReceivedCallback {
    private static final int MAX_EXPIRY_TIME_MILLIS = 10*60;//10 mins
    private List<TextView> m_pinTextViews = new ArrayList<>();
    private EditText m_hiddenEditText;
    private ImageButton m_confirmButton;
    private TextView m_changeNumberButton;
    private TextView m_errorText;
    private TextView m_expiryText;
    private String m_token;
    private String m_phoneNumber;
    private IValidationCodeScreenCallback m_callback;
    private Timer m_timer;
    private TimerTask m_timerTask;
    private Handler mTimerHandler = new Handler();
    private long m_expiryScheduledTime;

    public void init(String token, String phoneNumber, IValidationCodeScreenCallback callback)
    {
        m_token = token;
        m_phoneNumber = phoneNumber;
        m_callback = callback;
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState)
    {   View view = inflater.inflate(R.layout.validation_enter_verification_code_layout, container, false);
        return view;
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState)
    {
        super.onViewCreated(view, savedInstanceState);

        m_pinTextViews.clear();
        m_pinTextViews.add((TextView) view.findViewById(R.id.code_1));
        m_pinTextViews.add((TextView) view.findViewById(R.id.code_2));
        m_pinTextViews.add((TextView) view.findViewById(R.id.code_3));
        m_pinTextViews.add((TextView) view.findViewById(R.id.code_4));

        m_errorText = (TextView)view.findViewById(R.id.error_text);
        m_errorText.setVisibility(View.INVISIBLE);

        m_expiryText = (TextView)view.findViewById(R.id.expiry_text);
        setExpiryText(MAX_EXPIRY_TIME_MILLIS);

        if(m_hiddenEditText == null)
        {
            m_hiddenEditText = (EditText) view.findViewById(R.id.hidden_edit_text);
            m_hiddenEditText.addTextChangedListener(this);
        }

        m_confirmButton = (ImageButton) view.findViewById(R.id.confirm_button);
        m_confirmButton.setOnClickListener(this);

        m_changeNumberButton = (TextView) view.findViewById(R.id.change_number_button);
        m_changeNumberButton.setOnClickListener(this);

        for(TextView tv : m_pinTextViews)
        {
            tv.setOnClickListener(this);
        }

        m_expiryScheduledTime = System.currentTimeMillis() + MAX_EXPIRY_TIME_MILLIS * 1000;
        requestFocusOnCodeInput();
    }

    @Override
    public void onResume()
    {
        super.onResume();
        startTimer();
    }

    @Override
    public void onPause()
    {
        super.onPause();
        stopTimer();
    }

    @Override
    public void onClick(View v)
    {
        switch (v.getId()) {
            case R.id.confirm_button:
                handleConfirmButtonSelected();
                break;

            case R.id.change_number_button:
                handleResendCodeButtonSelected();
                break;

            default:
                requestFocusOnCodeInput();
        }

    }

    private void requestFocusOnCodeInput()
    {
        m_hiddenEditText.setText("");
        m_hiddenEditText.requestFocus();
        showSoftKeyboard(m_hiddenEditText);
    }

    public void showSoftKeyboard(EditText editText) {
        if (editText == null)
        {
            return;
        }

        InputMethodManager imm = (InputMethodManager)getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.showSoftInput(editText, 0);
        getActivity().getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_VISIBLE);
    }

    public void dismissKeyboard()
    {
        View view = getActivity().getCurrentFocus();
        if (view != null)
        {
            InputMethodManager imm = (InputMethodManager)getActivity().getSystemService(Context.INPUT_METHOD_SERVICE);
            imm.hideSoftInputFromWindow(view.getApplicationWindowToken(), 0);
            getActivity().getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);
        }
    }

    @Override
    public void beforeTextChanged(CharSequence s, int start, int count, int after)
    {

    }

    @Override
    public void onTextChanged(CharSequence s, int start, int before, int count)
    {
        resetAllTextViewsAccordingToPinEntered();

        if(m_hiddenEditText.getText().length() == 4)
        {
            m_confirmButton.setEnabled(true);
            dismissKeyboard();
        }
        else
        {
            m_confirmButton.setEnabled(false);
        }
    }

    @Override
    public void afterTextChanged(Editable s)
    {

    }

    private void resetAllTextViewsAccordingToPinEntered()
    {
        for(int i=0 ; i<m_pinTextViews.size() ; i++)
        {
            if(m_hiddenEditText.getText().length()>i)
            {
                m_pinTextViews.get(i).setText(m_hiddenEditText.getText().toString().charAt(i) + "");
                m_pinTextViews.get(i).setSelected(true);
            }
            else
            {
                m_pinTextViews.get(i).setText("");
                m_pinTextViews.get(i).setSelected(false);
            }
        }
    }

    private void stopTimer()
    {
        if(m_timer != null)
        {
            m_timer.cancel();
            m_timer.purge();
            m_timer = null;
        }
    }

    private void startTimer()
    {
        int remainingTime = (int) ((m_expiryScheduledTime - System.currentTimeMillis()) / 1000);
        if(remainingTime <= 0 && m_timer != null)
        {
            stopTimer();
            notifyVerificationCodeExpired();
            return;
        }

        stopTimer();
        m_timer = new Timer();
        m_timerTask = new TimerTask()
        {
            public void run()
            {
                mTimerHandler.post(new Runnable()
                {
                    public void run()
                    {
                        int remainingTime = (int) ((m_expiryScheduledTime - System.currentTimeMillis()) / 1000);
                        setExpiryText(remainingTime);
                        if(remainingTime <= 0)
                        {
                            stopTimer();
                            notifyVerificationCodeExpired();
                        }
                    }
                });
            }
        };

        m_timer.schedule(m_timerTask, 0, 1000);
    }

    private void setExpiryText(int timeSec)
    {
        m_expiryText.setText(formatTime(timeSec));
    }

    private String formatTime(int timeSec)
    {
        if(timeSec <= 0)
        {
            return "00:00";
        }

        int min = timeSec / 60;
        int sec = timeSec % 60;
        String minStr = min<10 ? "0"+min : min + "";
        String secStr = sec<10 ? "0"+sec : sec + "";
        return minStr + ":" + secStr;
    }

    private void handleConfirmButtonSelected()
    {
        if(m_callback != null)
        {
            m_callback.onValidationCodeEntered(Integer.parseInt(m_hiddenEditText.getText().toString()), m_token, this);
        }
        dismissKeyboard();
    }

    private void handleResendCodeButtonSelected()
    {
        if(m_callback != null)
        {
            m_callback.onResendCodeRequest(m_phoneNumber, this);
        }
    }

    @Override
    public void onError(String message)
    {
        if(message.length()>0)
        {
            m_errorText.setVisibility(View.VISIBLE);
            m_errorText.setText(message);
            requestFocusOnCodeInput();
        }
        else
        {
            m_errorText.setText("");
            m_errorText.setVisibility(View.INVISIBLE);
        }
    }

    @Override
    public void onResendResponseReceived(String token)
    {
        resetTokenAndValidationCode(token);
        notifyCodeResent();
    }

    private void resetTokenAndValidationCode(String token)
    {
        m_token = token;
        requestFocusOnCodeInput();
        m_expiryScheduledTime = System.currentTimeMillis() + MAX_EXPIRY_TIME_MILLIS * 1000;
        startTimer();
        onError("");
    }

    public void notifyVerificationCodeExpired()
    {
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(new ContextThemeWrapper(getActivity(), R.style.AlertDialogCustom));
        alertDialogBuilder.setTitle("Code expired")
                .setMessage("Validation code has been expired")
                .setCancelable(false)
                .setPositiveButton("Ok", new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                        if(m_callback!=null)
                        {
                            m_callback.onValidationCodeExpired();
                        }
                    }
                });
        AlertDialog alert = alertDialogBuilder.create();
        alert.show();
    }

    public void notifyCodeResent()
    {
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(new ContextThemeWrapper(getActivity(), R.style.AlertDialogCustom));
        alertDialogBuilder.setTitle("Success")
                .setMessage("Validation code has been resent")
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

}
