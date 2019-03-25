package com.eegeo.utils;

import android.app.AlertDialog;
import android.content.ActivityNotFoundException;
import android.content.ComponentName;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;
import android.util.Log;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.qrscanview.QRScanView;

import java.util.List;

public class Utils
{
    public static void openARApplication(MainActivity activity)
    {
        String applicationPackage = "com.netsoltech.arindoor";

        Intent launchIntent = activity.getPackageManager().getLaunchIntentForPackage(applicationPackage);
        if (launchIntent != null) {
            activity.startActivity(launchIntent);
        }
        else {

                AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(activity);
                alertDialogBuilder.setTitle("Error")
                        .setMessage("Eagle AR app is not installed on your device")
                        .setCancelable(false)
                        .setPositiveButton("OK", new DialogInterface.OnClickListener()
                        {
                            @Override
                            public void onClick(DialogInterface dialog, int which)
                            {
                                dialog.dismiss();
                            }
                        });
                AlertDialog alert = alertDialogBuilder.create();
                alert.show();
        }

    }
}
