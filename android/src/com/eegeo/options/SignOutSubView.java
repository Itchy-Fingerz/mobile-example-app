package com.eegeo.options;

import android.os.SystemClock;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.netsoltech.jcgroup.mobileexampleapp.R;

import java.util.Timer;
import java.util.TimerTask;

public class SignOutSubView
{
	private MainActivity m_activity = null;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private Runnable m_confirmationCallback = null;
    private boolean m_isDisplayed = false;
    private View m_confirmButton = null;
	private View m_cancelButton = null;
	private View m_closeButton = null;
	private View m_container_confirm = null;
	private View m_container_progress = null;
	private View m_spinner = null;
	private TextView m_content = null;

    private enum Containers
	{
		CONFIRMATION, PROGRESS, DONE
	}

    public SignOutSubView(MainActivity activity)
    {
    	m_activity = activity;
        m_uiRoot = (RelativeLayout)activity.findViewById(R.id.ui_container);
        m_view = activity.getLayoutInflater().inflate(R.layout.sign_out_ceremony_layout, m_uiRoot, false);
        m_uiRoot.addView(m_view);
        
        m_confirmButton = m_view.findViewById(R.id.sign_out_ceremony_confirm_button);
		m_cancelButton = m_view.findViewById(R.id.sign_out_ceremony_cancel_button);
		m_closeButton = m_view.findViewById(R.id.sign_out_ceremony_close_button);
		m_container_confirm = m_view.findViewById(R.id.sign_out_ceremony_view_container);
		m_container_progress = m_view.findViewById(R.id.sign_out_ceremony_progress_container);
		m_spinner = m_view.findViewById(R.id.sign_out_ceremony_progress_spinner);
        m_content = (TextView) m_view.findViewById(R.id.sign_out_ceremony_progress_message);

        m_confirmButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View arg0) {
		        handleConfirmClicked();
			}
		});

        View.OnClickListener closeListener = new View.OnClickListener() {
			public void onClick(View arg0) {
				resetState();
				m_uiRoot.removeView(m_view);
			}
		};

		m_cancelButton.setOnClickListener(closeListener);
		m_closeButton.setOnClickListener(closeListener);

		setContainer(Containers.CONFIRMATION);

        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);
        
        resetState();
    }

	private void resetState()
	{
		m_isDisplayed = false;
		m_confirmationCallback = null;

		m_view.setVisibility(View.GONE);
	}

    public void displayWarning(Runnable confirmationCallback)
    {
    	assert(confirmationCallback != null);
    	assert(m_confirmationCallback == null);
    	assert(!m_isDisplayed);
    	
    	m_isDisplayed = true;
    	m_confirmationCallback = confirmationCallback;

        m_view.setVisibility(View.VISIBLE);
    }
    
    public void concludeCeremony()
    {
    	assert(m_isDisplayed);

		setContainer(Containers.DONE);
    }

    private void setContainer(Containers container)
	{
		switch (container)
		{
			case CONFIRMATION:
				m_closeButton       .setVisibility(View.INVISIBLE);
				m_container_confirm .setVisibility(View.VISIBLE);
				m_container_progress.setVisibility(View.INVISIBLE);
				break;
			case PROGRESS:
				m_closeButton       .setVisibility(View.INVISIBLE);
				m_container_confirm .setVisibility(View.INVISIBLE);
				m_container_progress.setVisibility(View.VISIBLE);

				m_spinner.setVisibility(View.VISIBLE);
				m_content.setText(R.string.sign_out_working);
				break;
			case DONE:
				m_closeButton       .setVisibility(View.VISIBLE);
				m_container_confirm .setVisibility(View.INVISIBLE);
				m_container_progress.setVisibility(View.VISIBLE);

				m_spinner.setVisibility(View.INVISIBLE);
				m_content.setText(R.string.sign_out_done);
				break;
		}
	}

    private void handleConfirmClicked()
    {
    	assert(m_isDisplayed);

		setContainer(Containers.PROGRESS);

        m_confirmationCallback.run();
    }
}
