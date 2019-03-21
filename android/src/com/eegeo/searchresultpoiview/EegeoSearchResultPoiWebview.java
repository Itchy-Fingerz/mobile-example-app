// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchresultpoiview;

import android.annotation.SuppressLint;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Handler;
import android.text.util.Linkify;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IBackButtonListener;
import com.eegeo.helpers.TintablePinToggleButton;
import com.eegeo.tags.TagResources;
import com.netsoltech.eagleApp.R;

import java.util.regex.Pattern;

public class EegeoSearchResultPoiWebview implements View.OnClickListener, IBackButtonListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;

    private View m_closeButton = null;
    private WebView m_webView = null;

	private boolean m_handlingClick = false;


    @SuppressLint("NewApi")
	public EegeoSearchResultPoiWebview(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_result_poi_eegeo_webview_layout, m_uiRoot, false);
       
        m_closeButton = m_view.findViewById(R.id.search_result_poi_webview_close_button);
        m_webView = (WebView)m_view.findViewById(R.id.webview);

        m_activity.recursiveDisableSplitMotionEvents((ViewGroup)m_view);
        
        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);

        m_webView.setWebViewClient(new WebViewClient()
        {
            @Override
            public void onReceivedError(WebView view, int errorCode, String description, String failingUrl)
            {
                /*
                 * A lot of the examples suggest something like this:
                 * if(errorCode==404)
                 * However this does not give the expected results, instead use the defined constants:
                 * ERROR_HOST_LOOKUP
                 * ERROR_FILE_NOT_FOUND
                */

                view.loadUrl("file:///android_asset/page_not_found.html");
            }
        });
        
        m_closeButton.setOnClickListener(this);

        m_activity.addBackButtonPressedListener(this);
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
        m_activity.removeBackButtonPressedListener(this);
    }

    public void displayPoiInfo(final String customViewUrl)
    {
    	m_closeButton.setEnabled(true);

        m_view.setVisibility(View.VISIBLE);
        m_view.requestFocus();

        m_handlingClick = false;
        
        if(!customViewUrl.equals("")) {
            m_webView.getSettings().setUseWideViewPort(true);
            m_webView.getSettings().setLoadWithOverviewMode(true);
            m_webView.loadUrl(customViewUrl);

            boolean canUseJavascript = SearchResultPoiViewJniMethods.isJavascriptWhitelisted(m_nativeCallerPointer, customViewUrl);
            m_webView.getSettings().setJavaScriptEnabled(canUseJavascript);

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

        SearchResultPoiViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
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
