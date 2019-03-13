// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.qrscanview;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.net.Uri;
import android.os.Handler;
import android.os.Looper;
import android.provider.MediaStore;
import android.support.v4.app.ActivityCompat;
import android.view.HapticFeedbackConstants;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.helpers.IRuntimePermissionResultHandler;
import com.netsoltech.eagleApp.R;
import com.google.zxing.Result;

import java.util.List;

import me.dm7.barcodescanner.zxing.ZXingScannerView;

public class QRScanView implements View.OnClickListener, ZXingScannerView.ResultHandler, IRuntimePermissionResultHandler
{
    private static final int CAMERA_PERMISSION_REQUEST_CODE = 1000;
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_view = null;
    private RelativeLayout m_uiRoot = null;
    private View m_closeButton = null;
    private RelativeLayout m_qrScanContainerView;
    private ZXingScannerView m_scannerView;
    private View m_qrScanSuccessIcon;

    public QRScanView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);

        m_view = m_activity.getLayoutInflater().inflate(R.layout.qr_scan_layout, m_uiRoot, false);
        m_closeButton = m_view.findViewById(R.id.qr_scan_view_close_button);
        m_qrScanSuccessIcon = m_view.findViewById(R.id.qr_scan_success_icon);

        m_qrScanContainerView = m_view.findViewById(R.id.qr_scan_container_view);

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
//        onQRScanCompleted("wrld://fixedlocation/indoor/31.496739/74.421984/EIM-908710f5-3ed3-408d-a92b-c7749d9f1ae1/0");

        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);

        m_activity.getRuntimePermissionDispatcher().addRuntimePermissionResultHandler(this);

    }

    private void onQRScanCompleted(String scanData)
    {
        Uri url = Uri.parse(scanData);
        String host = url.getHost();
        final List<String> pathSegments = url.getPathSegments();

        m_scannerView.performHapticFeedback(HapticFeedbackConstants.VIRTUAL_KEY, HapticFeedbackConstants.FLAG_IGNORE_GLOBAL_SETTING);
        m_scannerView.stopCamera();

        if (host!=null && host.equals("fixedlocation"))
        {
            if(pathSegments!=null)
            {
                if(pathSegments.get(0).equals("indoor"))
                {
                    if(pathSegments.size() == 8)
                    {
                        m_qrScanSuccessIcon.setVisibility(View.VISIBLE);

                        new Handler(Looper.getMainLooper()).postDelayed(new Runnable()
                        {
                            @Override
                            public void run()
                            {
                                double lat = Double.parseDouble(pathSegments.get(1));
                                double lng = Double.parseDouble(pathSegments.get(2));
                                String buildingId = pathSegments.get(3);
                                int floorNumber = Integer.parseInt(pathSegments.get(4));
                                double orientation = Double.parseDouble(pathSegments.get(5));
                                double zoomLevel = Double.parseDouble(pathSegments.get(6));
                                double tiltAngle = Double.parseDouble(pathSegments.get(7));
                                QRScanViewJniMethods.OnIndoorQRScan(m_nativeCallerPointer,lat,lng,buildingId,floorNumber,orientation,zoomLevel,tiltAngle);
                                QRScanViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
                            }
                        }, 1000);

                    }
                    else
                    {
                        onQRError();
                    }
                }
                else if(pathSegments.get(0).equals("outdoor"))
                {
                    if(pathSegments.size() == 6)
                    {
                        m_qrScanSuccessIcon.setVisibility(View.VISIBLE);
                        new Handler(Looper.getMainLooper()).postDelayed(new Runnable()
                        {
                            @Override
                            public void run()
                            {
                                double lat = Double.parseDouble(pathSegments.get(1));
                                double lng = Double.parseDouble(pathSegments.get(2));
                                double orientation = Double.parseDouble(pathSegments.get(3));
                                double zoomLevel = Double.parseDouble(pathSegments.get(4));
                                double tiltAngle = Double.parseDouble(pathSegments.get(5));
                                QRScanViewJniMethods.OnOutdoorQRScan(m_nativeCallerPointer,lat,lng,orientation,zoomLevel,tiltAngle);
                                QRScanViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
                            }
                        }, 1000);
                    }
                    else
                    {
                        onQRError();
                    }
                }
            }
            else
            {
                onQRError();
            }
        }
        else
        {
            onQRError();
        }
    }

    private void onQRError()
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
                        m_scannerView.setResultHandler(QRScanView.this);
                        m_scannerView.startCamera();
                    }
                });
        AlertDialog alert = alertDialogBuilder.create();
        alert.show();
    }

    public void destroy()
    {
        m_activity.getRuntimePermissionDispatcher().removeIRuntimePermissionResultHandler(this);
        m_uiRoot.removeView(m_view);
    }

    public void openQRScan()
    {
        m_closeButton.setEnabled(true);
        m_view.setVisibility(View.VISIBLE);
        m_qrScanSuccessIcon.setVisibility(View.GONE);
        m_view.requestFocus();

        if(m_activity.getRuntimePermissionDispatcher().hasCameraPermissionsWithCode(CAMERA_PERMISSION_REQUEST_CODE))
        {
            startQRScanCamera();
        }
    }

    public void dismissQRScan()
    {
        stopQRScanCamera();
        m_view.setVisibility(View.GONE);
    }

    private void startQRScanCamera()
    {
        m_scannerView = new ZXingScannerView(m_activity);
        m_scannerView.setBorderColor(Color.WHITE);
        m_scannerView.setBorderCornerRadius(m_activity.dipAsPx(5));
        m_scannerView.setBorderLineLength(m_activity.dipAsPx(50));
        m_scannerView.setIsBorderCornerRounded(true);
        m_scannerView.setSquareViewFinder(true);
        m_scannerView.setBorderStrokeWidth(m_activity.dipAsPx(6));
        m_scannerView.setMaskColor(Color.TRANSPARENT);
        m_scannerView.setLaserEnabled(false);

        m_qrScanContainerView.addView(m_scannerView);
        m_scannerView.setResultHandler(this);
        m_scannerView.startCamera();
    }

    private void stopQRScanCamera()
    {
        if(m_scannerView!=null)
        {
            m_scannerView.stopCamera();
        }
        m_qrScanContainerView.removeAllViews();
    }

    public void onClick(View view)
    {
        m_closeButton.setEnabled(false);
        QRScanViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
    }

    @Override
    public void handleResult(Result result)
    {
        onQRScanCompleted(result.getText());
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults)
    {
        if(requestCode != CAMERA_PERMISSION_REQUEST_CODE)
            return;

        // If request is cancelled, the result arrays are empty.
        if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
        {
            Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
            if(takePictureIntent.resolveActivity(m_activity.getPackageManager()) != null)
            {
                startQRScanCamera();
            }
            else
            {
                showCameraErrorDialog();
            }
        }
        else
        {
            // If any of the permission is denied, we can't use the camera
            // properly, so we will show the dialog with agree or cancel dialog
            showPermissionRequiredDialog(m_activity);
        }
        return;

    }

    private void showCameraErrorDialog()
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(m_activity);
        builder.setTitle("Error");
        builder.setMessage("Error opening camera. Make sure device camera is not 'disabled'");
        builder.setNegativeButton("Ok", null);
        builder.setCancelable(false);
        builder.show();
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
                        if (ActivityCompat.shouldShowRequestPermissionRationale(context, Manifest.permission.CAMERA))
                        {
                            // Checking Permissions again
                            m_activity.getRuntimePermissionDispatcher().hasCameraPermissionsWithCode(CAMERA_PERMISSION_REQUEST_CODE);
                        }
                        else
                        {
                            // Open App Settings Page
                            m_activity.getRuntimePermissionDispatcher().startAppSettings(context);
                        }
                        break;

                    case DialogInterface.BUTTON_NEGATIVE:
                        QRScanViewJniMethods.CloseButtonClicked(m_nativeCallerPointer);
                        break;
                }
            }
        };

        AlertDialog.Builder builder = new AlertDialog.Builder(context);
        builder.setMessage(context.getResources().getString(R.string.required_camera_permission_text))
                .setPositiveButton(context.getResources().getString(R.string.ok_text), dialogClickListener)
                .setNegativeButton(context.getResources().getString(R.string.cancel_text), dialogClickListener).show();
    }

}
