package com.eegeo.mobileexampleapp.validation;

import android.content.Context;
import android.graphics.Paint;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import com.netsoltech.jcgroup.mobileexampleapp.R;

/**
 * Created by najhiullah on 13/03/2018.
 */

public class EnterNumberFragment extends Fragment implements View.OnClickListener, IOnErrorResponse, TextWatcher
{
    private TextView m_numberCountryCodeText;
    private EditText m_numberInputField;
    private ImageButton m_verifyButton;
    private INumberEnteredCallback m_callback;
    private TextView m_errorText;

    public void init(INumberEnteredCallback callback)
    {
        m_callback = callback;
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {   View view = inflater.inflate(R.layout.validation_enter_phone_number_layout, container, false);
        return view;
    }

    @Override
    public void onViewCreated(final View view, Bundle savedInstanceState)
    {
        super.onViewCreated(view, savedInstanceState);

        m_numberCountryCodeText = (TextView)view.findViewById(R.id.number_country_code_text);
        m_numberInputField = (EditText)view.findViewById(R.id.number_input_field);
        m_numberInputField.addTextChangedListener(this);

        m_verifyButton = (ImageButton) view.findViewById(R.id.verify_button);
        m_verifyButton.setOnClickListener(this);
        m_verifyButton.setEnabled(false);

        m_errorText = (TextView)view.findViewById(R.id.error_text);
        m_errorText.setVisibility(View.INVISIBLE);

        view.addOnLayoutChangeListener(new View.OnLayoutChangeListener()
        {
            @Override
            public void onLayoutChange(View v, int left, int top, int right, int bottom, int oldLeft, int oldTop, int oldRight, int oldBottom)
            {
                view.removeOnLayoutChangeListener(this);

                //For keyboard overlapping edit text
                int editHeight = m_numberInputField.getHeight();
                Paint.FontMetrics fontMetrics = m_numberInputField.getPaint().getFontMetrics();
                float textHeight = fontMetrics.bottom - fontMetrics.top + fontMetrics.leading;
                int remainingHeight = (int) (editHeight - textHeight);
                m_numberInputField.setPadding(0, remainingHeight / 2, 0, remainingHeight / 2);
            }
        });
    }

    @Override
    public void onClick(View v)
    {
        if(validatePhoneNumber())
        {
            if(m_callback != null)
            {
                m_callback.onNumberEntered(m_numberCountryCodeText.getText().toString().trim(), m_numberInputField.getText().toString().trim(), this);
            }
            onError("");
        }
        else
        {
            onError(getString(R.string.validation_phone_number_error_text));
        }

        dismissKeyboard();
    }

    private boolean validatePhoneNumber()
    {
        String phoneNumber = m_numberInputField.getText().toString().trim();
        if (phoneNumber.length() != 11)
        {
            return false;
        }
        else
        {
            return android.util.Patterns.PHONE.matcher(phoneNumber).matches();
        }
    }

    @Override
    public void onError(String message)
    {
        if(message.length()>0)
        {
            m_errorText.setVisibility(View.VISIBLE);
            m_errorText.setText(message);
        }
        else
        {
            m_errorText.setText("");
            m_errorText.setVisibility(View.INVISIBLE);
        }
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
        if(validatePhoneNumber())
        {
            m_verifyButton.setEnabled(true);
        }
        else
        {
            m_verifyButton.setEnabled(false);
        }
    }

    @Override
    public void afterTextChanged(Editable s)
    {

    }
}
