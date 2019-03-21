package com.eegeo.utils;

import android.content.ActivityNotFoundException;
import android.content.ComponentName;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;
import android.util.Log;

import com.eegeo.entrypointinfrastructure.MainActivity;

import java.util.List;

public class Utils
{
    public static void openARApplication(MainActivity activity)
    {
        String applicationPackage = "com.google.android.youtube";
        Intent intent = new Intent(Intent.ACTION_VIEW ,
                Uri.parse("https://www.youtube.com/channel/UCRmoG8dTnv0B7y9uoocikLw"));
        intent.setPackage("com.google.android.youtube");

        PackageManager manager = activity.getPackageManager();
        List<ResolveInfo> infos = manager.queryIntentActivities(intent, 0);
        if (infos.size() > 0)
        {
            activity.startActivity(intent);
        }
        else
        {
            Log.e("Utils", "Application not found. Redirecting to play store");
            Uri uri = Uri.parse("market://details?id=" + applicationPackage);
            Intent goToMarket = new Intent(Intent.ACTION_VIEW, uri);
            goToMarket.addFlags(Intent.FLAG_ACTIVITY_NO_HISTORY |
                    Intent.FLAG_ACTIVITY_NEW_DOCUMENT |
                    Intent.FLAG_ACTIVITY_MULTIPLE_TASK);
            try {
                activity.startActivity(goToMarket);
            } catch (ActivityNotFoundException error) {
                activity.startActivity(new Intent(Intent.ACTION_VIEW,
                        Uri.parse("http://play.google.com/store/apps/details?id=" + applicationPackage)));
            }
        }

    }
}
