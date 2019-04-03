// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.threesixtyinteractionview;

import android.content.Context;
import android.os.Handler;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.RelativeLayout;
import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IBackButtonListener;
import com.netsoltech.eagleApp.R;

public class ThreeSixtyInteractionView implements View.OnClickListener, IBackButtonListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private View m_closeButton = null;
    WebView m_webView = null;
    private boolean m_handlingClick = false;

    private RelativeLayout m_parentRL = null;
    public ThreeSixtyInteractionView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.threesixty_eegeo_webview_layout, m_uiRoot, false);

        m_closeButton = m_view.findViewById(R.id.search_result_poi_webview_close_button);

        m_parentRL = m_view.findViewById(R.id.search_result_poi_webview);

        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);

        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);

        m_closeButton.setOnClickListener(this);

        m_activity.addBackButtonPressedListener(this);

    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
        m_activity.removeBackButtonPressedListener(this);
    }

    public void displayPoiInfo(String customViewUrl)
    {
        m_closeButton.setEnabled(true);
        if(m_webView != null)
        {
            m_parentRL.removeView(m_webView);
            m_webView = null;
        }

        m_webView = new WebView(m_activity);
        ViewGroup.LayoutParams params = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        m_webView.setLayoutParams(params);
        m_parentRL.addView(m_webView,0);


        m_view.setVisibility(View.VISIBLE);
        m_view.requestFocus();

        m_handlingClick = false;

        if(!customViewUrl.equals("")) {
            m_webView.getSettings().setUseWideViewPort(true);
            m_webView.getSettings().setLoadWithOverviewMode(true);

            boolean canUseJavascript = true;
            m_webView.getSettings().setJavaScriptEnabled(canUseJavascript);

            if(customViewUrl.startsWith("http://360.focalrack.com"))
            {
                customViewUrl = customViewUrl.replaceFirst("http://360.focalrack.com","https://360.focalrack.com");
            }

            m_webView.setWebViewClient(new WebViewClient() {
                public void onPageFinished(WebView view, String url) {
                    boolean didZoom = m_webView.zoomOut();

                    final Handler handler = new Handler();
                    handler.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            m_webView.zoomOut();
                        }
                    }, 300);

                }
            });
            m_webView.loadUrl(customViewUrl);
        }
    }

    public void onClick(View view)
    {
        if(m_handlingClick)
        {
            return;
        }
        m_handlingClick = true;

        if(view == m_closeButton)
        {
            handleCloseClicked();
        }
    }

    public void dismissPoiInfo()
    {
        m_view.setVisibility(View.GONE);
    }

    private void handleCloseClicked()
    {
        m_view.setEnabled(false);

        dismissKeyboard();

        ThreeSixtyInteractionViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
    }

    @Override
    public boolean onBackButtonPressed() {
        if (m_view.getVisibility() == View.VISIBLE)
        {
            handleCloseClicked();
            return true;
        }
        return false;
    }

    private void dismissKeyboard()
    {
        InputMethodManager inputMethodManager = (InputMethodManager)m_view.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
        inputMethodManager.hideSoftInputFromWindow(m_view.getWindowToken(), 0);
    }
}
