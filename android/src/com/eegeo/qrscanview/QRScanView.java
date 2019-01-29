// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.qrscanview;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.net.Uri;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

import java.util.List;

public class QRScanView implements View.OnClickListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private View m_closeButton = null;

    public QRScanView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);

        m_view = m_activity.getLayoutInflater().inflate(R.layout.qr_scan_layout, m_uiRoot, false);
        m_closeButton = m_view.findViewById(R.id.qr_scan_view_close_button);

        RelativeLayout.LayoutParams layoutParams = (LayoutParams) m_view.getLayoutParams();
        if (m_activity.getResources().getBoolean(R.bool.isPhone)) 
        {
            layoutParams.topMargin = layoutParams.bottomMargin = layoutParams.leftMargin = layoutParams.rightMargin = m_activity.dipAsPx(20);
        }
        else 
        {
            layoutParams.topMargin = layoutParams.bottomMargin = m_activity.dipAsPx(80);
            layoutParams.leftMargin = layoutParams.rightMargin = (int) (m_uiRoot.getWidth() * 0.3f);
        }

        m_closeButton.setOnClickListener(this);
        View clickMeButton = m_view.findViewById(R.id.qr_scan_click_me);
        clickMeButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                onQRScanCompleted("wrld://fixedlocation/indoor/31.496739/74.421984/EIM-908710f5-3ed3-408d-a92b-c7749d9f1ae1/0");
            }
        });

        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);

    }

    private void onQRScanCompleted(String scanData)
    {
        Uri url = Uri.parse(scanData);
        String host = url.getHost();
        List<String> pathSegments = url.getPathSegments();

        if (host.equals("fixedlocation"))
        {
            if (pathSegments.size() == 5)
            {
                QRScanViewJniMethods.OnQRScan(m_nativeCallerPointer, host + pathSegments.get(0), Double.parseDouble(pathSegments.get(1)), Double.parseDouble(pathSegments.get(2)), pathSegments.get(3), Double.parseDouble(pathSegments.get(4)));
                QRScanViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
            }
            else if (pathSegments.size() == 4)
            {
                QRScanViewJniMethods.OnQRScan(m_nativeCallerPointer, host, Double.parseDouble(pathSegments.get(0)), Double.parseDouble(pathSegments.get(1)), pathSegments.get(2), Double.parseDouble(pathSegments.get(3)));
                QRScanViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
            }
            else
            {
                showQRErrorDialog();
            }
        }
        else
        {
            showQRErrorDialog();
        }
    }

    private void showQRErrorDialog()
    {
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(m_activity);
        alertDialogBuilder.setTitle("QR Scan Error")
                .setMessage("It is not a valid QR Code.")
                .setCancelable(false)
                .setPositiveButton("Ok", new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which)
                    {
                        dialog.dismiss();
                        QRScanViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
                    }
                });
        AlertDialog alert = alertDialogBuilder.create();
        alert.show();
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
    }

    public void displayContent(final String content)
    {

    }

    public void showHiddenText()
    {
        QRScanViewJniMethods.LogoLongPress(m_nativeCallerPointer);
    }

    public void openQRScan()
    {
        m_closeButton.setEnabled(true);
        m_view.setVisibility(View.VISIBLE);
        m_view.requestFocus();
    }

    public void dismissQRScan()
    {
        m_view.setVisibility(View.GONE);
    }

    public void onClick(View view)
    {
        m_closeButton.setEnabled(false);
        QRScanViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
    }
}
