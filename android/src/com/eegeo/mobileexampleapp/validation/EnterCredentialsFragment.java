package com.eegeo.mobileexampleapp.validation;

import android.content.Context;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.text.Editable;
import android.text.TextWatcher;
import android.text.method.PasswordTransformationMethod;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import com.eegeo.mobileexampleapp.R;


/**
 * Created by najhiullah on 13/03/2018.
 */

public class EnterCredentialsFragment extends Fragment implements View.OnClickListener, IOnErrorResponse, TextWatcher
{
    private EditText m_emailInputField;
    private EditText m_passwordInputField;
    private ImageButton m_verifyButton;
    private ICredentialsEnteredCallback m_callback;
    private TextView m_errorText;

    public void init(ICredentialsEnteredCallback callback)
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
    {   View view = inflater.inflate(R.layout.validation_enter_credentials_layout, container, false);
        return view;
    }

    @Override
    public void onViewCreated(final View view, Bundle savedInstanceState)
    {
        super.onViewCreated(view, savedInstanceState);

        m_emailInputField = view.findViewById(R.id.email_input_field);
        m_emailInputField.addTextChangedListener(this);

        m_passwordInputField = view.findViewById(R.id.password_input_field);
        m_passwordInputField.setTypeface(Typeface.DEFAULT);
        m_passwordInputField.setTransformationMethod(new PasswordTransformationMethod());
        m_passwordInputField.addTextChangedListener(this);

        m_verifyButton = view.findViewById(R.id.verify_button);
        m_verifyButton.setOnClickListener(this);
        m_verifyButton.setEnabled(false);

        m_errorText = view.findViewById(R.id.error_text);
        m_errorText.setVisibility(View.INVISIBLE);

        view.addOnLayoutChangeListener(new View.OnLayoutChangeListener()
        {
            @Override
            public void onLayoutChange(View v, int left, int top, int right, int bottom, int oldLeft, int oldTop, int oldRight, int oldBottom)
            {
                view.removeOnLayoutChangeListener(this);

                //For keyboard overlapping edit text
                int editHeight = m_emailInputField.getHeight();
                Paint.FontMetrics fontMetrics = m_emailInputField.getPaint().getFontMetrics();
                float textHeight = fontMetrics.bottom - fontMetrics.top + fontMetrics.leading;
                int remainingHeight = (int) (editHeight - textHeight);
                m_emailInputField.setPadding(m_emailInputField.getPaddingLeft(), remainingHeight / 2, m_emailInputField.getPaddingRight(), remainingHeight / 2);

                m_passwordInputField.setPadding(m_passwordInputField.getPaddingLeft(), remainingHeight / 2, m_passwordInputField.getPaddingRight(), remainingHeight / 2);
            }
        });
    }

    @Override
    public void onClick(View v)
    {
        if(m_callback != null)
        {
            m_callback.onCredentialsEntered(m_emailInputField.getText().toString().trim(), m_passwordInputField.getText().toString().trim(), this);
        }
        onError("");
        dismissKeyboard();
    }

    private boolean validateCredentials()
    {
        String emailPattern = "[a-zA-Z0-9._-]+@[a-z]+\\.+[a-z]+";
        String email = m_emailInputField.getText().toString().trim();
        String password = m_passwordInputField.getText().toString().trim();

        if (email.length() == 0 || password.length() == 0)
        {
            return false;
        }
        else if (!email.matches(emailPattern))
        {
            return false;
        }
        else
        {
            return true;
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
        if(validateCredentials())
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
