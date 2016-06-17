// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
package com.eegeo.interiorsexplorer;

import java.util.ArrayList;
import java.util.List;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.mobileexampleapp.R;

import android.graphics.Color;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class InteriorsExplorerView implements View.OnClickListener, View.OnTouchListener
{
    protected MainActivity m_activity = null;
    protected long m_nativeCallerPointer;
    private View m_uiRootView = null;
    private View m_topPanel = null;
    
    private ImageView m_backButton = null;
    private TextView m_floorNameView = null;
    
    private RelativeLayout m_floorButton = null;
    private TextView m_floorButtonText = null;
    private Boolean m_draggingFloorButton;

    private final long m_stateChangeAnimationTimeMilliseconds = 200;
    
    private float m_topYPosActive;
    private float m_topYPosInactive;

    private RelativeLayout m_floorListContainer;
    private ListView m_floorList;
    private float m_leftXPosActive;
    private float m_leftXPosInactive;
    
    private InteriorsFloorListAdapter m_floorListAdapter = null;
    private float m_previousYCoordinate;
    
    private boolean m_canProcessButtons;
    
    // TODO: Replace these with refs to UX iteration color scheme.
    private final int TextColorNormal = Color.parseColor("#1256B0");
    private final int TextColorDown = Color.parseColor("#CDFC0D");
    private final float ButtonSize;
    private final float ListItemHeight;

    public InteriorsExplorerView(MainActivity activity, long nativeCallerPointer)
    {
        m_activity = activity;
        m_nativeCallerPointer = nativeCallerPointer;

        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        m_uiRootView = m_activity.getLayoutInflater().inflate(R.layout.interiors_explorer_layout, uiRoot, false);
        
        m_topPanel = m_uiRootView.findViewById(R.id.top_panel);
        
        m_backButton = (ImageView)m_uiRootView.findViewById(R.id.back_button);
        m_backButton.setOnClickListener(this);
        
        m_floorNameView = (TextView)m_uiRootView.findViewById(R.id.floor_name);
        
        m_floorListContainer = (RelativeLayout)m_uiRootView.findViewById(R.id.interiors_floor_list_container);
        m_floorList = (ListView)m_uiRootView.findViewById(R.id.interiors_floor_item_list);
        
        m_floorListAdapter = new InteriorsFloorListAdapter(m_activity, R.layout.interiors_floor_list_item);
        m_floorList.setAdapter(m_floorListAdapter);
        
        m_floorButton = (RelativeLayout)m_uiRootView.findViewById(R.id.interiors_floor_list_button);
        m_floorButtonText = (TextView)m_uiRootView.findViewById(R.id.interiors_floor_list_button_text);
        m_floorButtonText.setTextColor(TextColorNormal);
        m_draggingFloorButton = false;
        
        // TODO: Move to Dimens values resource when integrated with Search UX changes.
        ButtonSize = m_activity.dipAsPx(64.0f);
        ListItemHeight = m_activity.dipAsPx(50.0f);
        
        m_floorButton.setOnTouchListener(this);
        
        m_uiRootView.addOnLayoutChangeListener(new View.OnLayoutChangeListener() 
        {
			@Override
			public void onLayoutChange(View v, int left, int top, int right,
					int bottom, int oldLeft, int oldTop, int oldRight,
					int oldBottom) 
			{				
		    	final float screenWidth = uiRoot.getWidth();
		    	
		    	float controlWidth = m_topPanel.getWidth();
		    	float controlHeight = m_topPanel.getHeight();
		    	
		    	m_topYPosActive = m_activity.dipAsPx(20);
		    	m_topYPosInactive = -controlHeight;
		    	
		    	m_topPanel.setX((screenWidth * 0.5f) - (controlWidth * 0.5f));
		    	m_topPanel.setY(m_topYPosInactive);
		    	
		    	controlWidth = m_floorListContainer.getWidth();
		    	controlHeight = m_floorListContainer.getHeight();
		    	
		    	m_leftXPosActive = screenWidth - (m_backButton.getWidth() / 2.0f  + m_activity.getResources().getDimension(R.dimen.menu_button_margin) + controlWidth / 2.0f);
		    	m_leftXPosInactive = screenWidth;
		    	
		    	m_floorListContainer.setX(m_leftXPosInactive);
		    	
		    	m_uiRootView.removeOnLayoutChangeListener(this);
			}
        });
        uiRoot.addView(m_uiRootView);
        
        hideFloorLabels();
    }
    
    private int getListViewHeight(ListView list) 
    {
        // Const out some of these.
        return list.getCount() * (int)ListItemHeight + (int)(ButtonSize - ListItemHeight);
   }

    public void destroy()
    {
        final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
        uiRoot.removeView(m_uiRootView);
        m_uiRootView = null;
    }
    
    public void updateFloors(String[] floorShortNames, int currentlySelectedFloorIndex)
    {
    	List<String> temp = new ArrayList<String>();
    	for(int i = floorShortNames.length - 1; i >= 0; --i)
    	{
    		temp.add(floorShortNames[i]);
    	}
    	
    	m_floorListAdapter.setData(temp);
    	float controlHeight = getListViewHeight(m_floorList);
    	RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams)m_floorListContainer.getLayoutParams();
    	layoutParams.height = (int)controlHeight;
    	m_floorListContainer.setLayoutParams(layoutParams);
    	
    	refreshFloorIndicator(currentlySelectedFloorIndex);
    	moveButtonToFloorIndex(currentlySelectedFloorIndex, false);
    	
    	boolean floorSelectionEnabled = floorShortNames.length > 1;
    	m_floorListContainer.setVisibility(floorSelectionEnabled ? View.VISIBLE : View.GONE);
    }
    
    private void moveButtonToFloorIndex(int floorIndex, Boolean shouldAnimate)
    {
    	int floorCount = m_floorListAdapter.getCount();
    	float topY = (m_floorList.getY()) + (ListItemHeight*0.5f) - m_floorButton.getWidth()*0.5f;
    	float newY = topY + ((floorCount-1)-floorIndex) * ListItemHeight;
    	newY = Math.max(0.0f, Math.min(getListViewHeight(m_floorList)-m_floorButton.getHeight(), newY));
    	
    	if(shouldAnimate)
    	{
    		m_floorButton.animate()
    		.y(newY)
    		.setDuration(m_stateChangeAnimationTimeMilliseconds)
    		.start();
    	}
    	else
    	{
    		m_floorButton.setY(newY);
    	}
    }
    
    public void setFloorName(String name)
    {
    	m_floorNameView.setText(name);
    }
    
    public void setSelectedFloorIndex(int index)
    {
    	refreshFloorIndicator(index);
    	
    	if(!m_draggingFloorButton)
    	{
    		moveButtonToFloorIndex(index, true);
    	}
    }
    
    public void setTouchEnabled(boolean enabled)
    {
    	m_canProcessButtons = enabled;
    }
    
    @Override
    public boolean onTouch(View view, MotionEvent event) {
		if(event.getAction() == MotionEvent.ACTION_DOWN)
		{
			startDraggingButton(event.getRawY());
		}
		else if(event.getAction() == MotionEvent.ACTION_MOVE)
		{
			updateDraggingButton(event.getRawY());
		}
		else if(event.getAction() == MotionEvent.ACTION_UP)
		{
			endDraggingButton();
		}
		return true;
	}
    
    private void startDraggingButton(float initialYCoordinate)
    {
    	showFloorLabels();
		m_floorButton.getBackground().setState(new int[] {android.R.attr.state_pressed});
		m_previousYCoordinate = initialYCoordinate;
		m_draggingFloorButton = true;
    }
    
    private void updateDraggingButton(float yCoordinate)
    {
    	float y = yCoordinate;
		float newY = m_floorButton.getY() + (y - m_previousYCoordinate);
		newY = Math.max(0.0f, Math.min(getListViewHeight(m_floorList)-ButtonSize, newY));
		m_floorButton.setY(newY);
		m_previousYCoordinate = y;
		float dragParameter = 1.0f - (newY / (getListViewHeight(m_floorList)-ButtonSize));
		InteriorsExplorerViewJniMethods.OnFloorSelectionDragged(m_nativeCallerPointer, dragParameter);;
    }
    
    private void endDraggingButton()
    {
    	hideFloorLabels();
		m_draggingFloorButton = false;
		m_floorButton.getBackground().setState(new int[] {});
		float dragParameter = 1.0f - (m_floorButton.getY() / (getListViewHeight(m_floorList)-ButtonSize));
		int floorCount = m_floorListAdapter.getCount()-1;
		int selectedFloor = Math.round(dragParameter * floorCount);
		moveButtonToFloorIndex(selectedFloor, true);
		InteriorsExplorerViewJniMethods.OnFloorSelected(m_nativeCallerPointer, selectedFloor);
    }

    @Override
    public void onClick(View view)
    {
        if(!m_canProcessButtons)
        {
        	return;
        }
        
    	if(view == m_backButton)
        {
    		InteriorsExplorerViewJniMethods.OnDismissedClicked(m_nativeCallerPointer);
        }
    }

    public void animateToActive()
    {
    	animateViewToY((int)m_topYPosActive);
        animateViewToX((int)m_leftXPosActive);
    }

    public void animateToInactive()
    {
        animateViewToY((int)m_topYPosInactive);
        animateViewToX((int)m_leftXPosInactive);
    }

    protected void animateViewToY(final int yAsPx)
    {
    	m_topPanel.animate()
        .y(yAsPx)
        .setDuration(m_stateChangeAnimationTimeMilliseconds);
    }
    
    protected void animateViewToX(final int xAsPx)
    {
    	m_floorListContainer.animate()
        .x(xAsPx)
        .setDuration(m_stateChangeAnimationTimeMilliseconds);
    }

    public void animateToIntermediateOnScreenState(final float onScreenState)
    {
        int viewYPx = (int)m_topPanel.getY();
        int newYPx = (int)(m_topYPosInactive + (int)(((m_topYPosActive - m_topYPosInactive) * onScreenState) + 0.5f));

        if(viewYPx != newYPx)
        {
        	m_topPanel.setY(newYPx);
        }
    }
    
    private void refreshFloorIndicator(int floorIndex)
    {
    	int nameIndex = (m_floorListAdapter.getCount()-1)-floorIndex;
    	m_floorButtonText.setText((String)m_floorListAdapter.getItem(nameIndex));
    }
    
    private void hideFloorLabels()
    {
        m_floorButtonText.setTextColor(TextColorNormal);

    	m_floorList.animate().alpha(0.5f).setDuration(m_stateChangeAnimationTimeMilliseconds);
    	
        int floorCount = m_floorListAdapter.getCount();
        for(int i = 0; i < floorCount; ++i)
        {
        	ViewGroup child = (ViewGroup)m_floorList.getChildAt(i);
        	TextView text = (TextView)child.findViewById(R.id.floor_name);
        	
        	text.animate().alpha(0.0f).setDuration(m_stateChangeAnimationTimeMilliseconds);
        }
    }
    
    private void showFloorLabels()
    {
    	m_floorButtonText.setTextColor(TextColorDown);
    	
    	int floorCount = m_floorListAdapter.getCount();
    	m_floorList.animate().alpha(1.0f).setDuration(m_stateChangeAnimationTimeMilliseconds);
        for(int i = 0; i < floorCount; ++i)
        {
        	ViewGroup child = (ViewGroup)m_floorList.getChildAt(i);
        	TextView text = (TextView)child.findViewById(R.id.floor_name);
        	
        	text.animate().alpha(1.0f).setDuration(m_stateChangeAnimationTimeMilliseconds);
        }
    }
}
