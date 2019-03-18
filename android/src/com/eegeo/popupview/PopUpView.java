package com.eegeo.popupview;

import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewTreeObserver;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;
import android.widget.RelativeLayout;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.netsoltech.eagleApp.R;

public class PopUpView implements View.OnTouchListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;

    private View m_view = null;
    private View m_popupImage;
    private RelativeLayout m_uiRoot = null;

    private boolean m_awaitingInput;
    private int m_imgWidth;
    private int m_imgHeight;

    public PopUpView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        m_uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.popup_layout, m_uiRoot, false);
        m_view.setOnTouchListener(this);

        m_popupImage = m_view.findViewById(R.id.img_popup);

        m_view.setVisibility(View.GONE);
        m_uiRoot.addView(m_view);

        m_view.getViewTreeObserver().addOnGlobalLayoutListener(new ViewTreeObserver.OnGlobalLayoutListener()
        {
            @Override
            public void onGlobalLayout()
            {
                m_view.getViewTreeObserver().removeOnGlobalLayoutListener(this);

                m_popupImage.measure(0,0);
                m_imgWidth = m_popupImage.getMeasuredWidth();
                m_imgHeight = m_popupImage.getMeasuredHeight();
            }
        });
    }

    public void destroy()
    {
        m_uiRoot.removeView(m_view);
    }

    public void show(double x, double y)
    {
        m_awaitingInput = true;
        m_view.setVisibility(View.VISIBLE);

//        RelativeLayout.LayoutParams params = (RelativeLayout.LayoutParams) m_popupImage.getLayoutParams();
//        params.leftMargin = (int) (x - m_imgWidth/2);
//        params.topMargin = (int) (y - m_activity.dipAsPx(100) - m_imgHeight/2);
//        m_popupImage.setLayoutParams(params);

        AlphaAnimation animation = new AlphaAnimation(0.0f, 1.0f);
        animation.setDuration(500);
        animation.setInterpolator(new DecelerateInterpolator());
        animation.setFillAfter(true);
        m_popupImage.clearAnimation();
        m_popupImage.startAnimation(animation);

    }

    public void hide()
    {
        if(m_awaitingInput)
        {
            m_awaitingInput = false;
            AlphaAnimation animation = new AlphaAnimation(1.0f, 0.0f);
            animation.setDuration(500);
            animation.setInterpolator(new DecelerateInterpolator());
            animation.setFillAfter(true);
            animation.setAnimationListener(new Animation.AnimationListener()
            {
                @Override
                public void onAnimationStart(Animation animation) { }

                @Override
                public void onAnimationEnd(Animation animation)
                {
                    m_view.setVisibility(View.GONE);
                }

                @Override
                public void onAnimationRepeat(Animation animation) { }
            });
            m_popupImage.clearAnimation();
            m_popupImage.startAnimation(animation);
        }

    }

    @Override
    public boolean onTouch(View view, MotionEvent motionEvent)
    {
        hide();
        return false;
    }
}
