package com.eegeo.mobileexampleapp.validation;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.ImageButton;
import android.widget.TextView;

import com.eegeo.mobileexampleapp.R;


/**
 * Created by najhiullah on 13/03/2018.
 */

public class ResponseStatusFragment extends Fragment implements View.OnClickListener
{
    private TextView m_statusText;
    private TextView m_doneButtonText;
    private ImageButton m_doneButton;
    private boolean m_isSuccess;
    private String m_statusMessage;
    private IResponseScreenCallback m_callback;

    public void init(boolean isSuccess, String message, IResponseScreenCallback callback)
    {
        m_isSuccess = isSuccess;
        m_statusMessage = message;
        m_callback = callback;
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {   View view = inflater.inflate(R.layout.validation_status_layout, container, false);
        return view;
    }

    @Override
    public void onResume()
    {
        super.onResume();
        dismissKeyboard();
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState)
    {
        super.onViewCreated(view, savedInstanceState);

        m_statusText = (TextView)view.findViewById(R.id.status_text);
        m_doneButton = (ImageButton) view.findViewById(R.id.done_button);
        m_doneButtonText = (TextView)view.findViewById(R.id.done_button_text);
        m_doneButton.setOnClickListener(this);

        if(m_isSuccess)
        {
            m_statusText.setText(m_statusMessage);
            m_statusText.setTextColor(Color.parseColor("#79c942"));
            m_doneButtonText.setText(R.string.validation_done_text);
        }
        else
        {
            m_statusText.setText(m_statusMessage);
            m_statusText.setTextColor(Color.RED);
            m_doneButtonText.setText(R.string.validation_go_back_text);
        }
    }

    @Override
    public void onClick(View v)
    {
        if(m_callback != null)
        {
            m_callback.onDoneButtonSelected(m_isSuccess);
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
}
