// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchmenu;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.netsoltech.jcgroup.mobileexampleapp.R;
import com.eegeo.searchproviders.MyTestSearchProvider;
import com.eegeo.searchproviders.QueryContext;

import android.app.SearchManager;
import android.app.SearchableInfo;
import android.content.Context;
import android.util.Log;
import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.searchproviders.SearchResultNavigationHandler;
import com.eegeo.tags.TagResources;
import com.eegeo.ui.IAnimatedView;
import com.eegeo.ui.IViewAnimator;
import com.eegeo.ui.ViewAnimator;
import com.wrld.widgets.search.WrldSearchWidget;
import com.wrld.widgets.search.model.MenuChild;
import com.wrld.widgets.search.model.MenuGroup;
import com.wrld.widgets.search.model.MenuOption;
import com.wrld.widgets.search.model.OnMenuOptionSelectedCallback;
import com.wrld.widgets.search.model.SearchQuery;
import com.wrld.widgets.search.model.SearchProviderQueryResult;
import com.wrld.widgets.search.model.SearchQueryModelListener;
import com.wrld.widgets.search.model.SearchResult;
import com.wrld.widgets.search.model.SearchResultsListener;
import com.wrld.widgets.search.model.TextChangedListener;
import com.wrld.widgets.search.view.MenuViewListener;
import com.wrld.widgets.search.view.SearchResultsViewListener;


import org.json.JSONObject;

import java.util.Arrays;
import java.util.Hashtable;
import java.util.List;

public class SearchWidgetView implements OnMenuOptionSelectedCallback,
                                        SearchResultsListener,
                                        IAnimatedView,
                                        SearchResultsViewListener,
                                        View.OnFocusChangeListener,
                                        MenuViewListener,
                                        SearchQueryModelListener,
                                        SearchResultNavigationHandler,
                                        TextChangedListener
{
    protected MainActivity m_activity;
    protected MyTestSearchProvider m_searchProvider;
    protected long m_nativeCallerPointer;
    protected View m_view;
    private IViewAnimator m_viewAnimator;
    protected WrldSearchWidget m_searchWidget;

    private boolean m_searchResultsAreVisible = true;
    private boolean m_menuIsOpen = false;
    private boolean m_searchTextboxIsInFocus = false;
    private boolean m_hasSearchResults = false;
    private boolean m_searchInProgress = false;

    private Hashtable<String, MenuOption> m_menuOptions
            = new Hashtable<String, MenuOption>();

    private Hashtable<String, MenuGroup> m_menuGroups
            = new Hashtable<String, MenuGroup>();

    private boolean m_hasPopulatedData = false;

    private final long m_stateChangeAnimationTimeMilliseconds = 200;

    public SearchWidgetView(MainActivity activity, long nativeCallerPointer,
                            MyTestSearchProvider searchProvider) {
        m_activity = activity;
        m_searchProvider = searchProvider;
        m_nativeCallerPointer = nativeCallerPointer;

        createView();
    }

    protected void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_widget_view_layout, uiRoot, false);
        uiRoot.addView(m_view);

        m_viewAnimator = new ViewAnimator(this, m_view);
        m_viewAnimator.registerLayoutChangeListener();

        m_searchWidget = (WrldSearchWidget) m_activity.getFragmentManager().findFragmentById(R.id.search_widget);
        m_searchWidget.addSearchProvider(m_searchProvider);
        m_searchWidget.addSuggestionProvider(m_searchProvider);

        m_searchProvider.addNavigationRequestCallback(this);

        m_searchWidget.getSearchResultsModel().addResultListener(this);

        m_searchWidget.getMenuViewObserver().addMenuListener(this);
        m_searchWidget.getSearchViewFocusObserver().addListener(this);
        m_searchWidget.getSearchResultsViewObserver().addListener(this);
        m_searchWidget.getSearchQueryModel().addListener(this);
        m_searchWidget.getTextChangedObserver().addTextChangedListener(this);

        SearchManager searchManager = (SearchManager) m_activity.getSystemService(Context.SEARCH_SERVICE);
        SearchableInfo searchableInfo = searchManager.getSearchableInfo(m_activity.getComponentName());
        m_searchWidget.setSearchableInfo(searchableInfo);

    }

    public void onSearchResultsReceived(SearchQuery searchQuery, List<SearchProviderQueryResult> list) {
        setHasSearchResults(true);
    }

    public void onSearchResultsCleared() {
        setHasSearchResults(false);

        SearchWidgetViewJniMethods.OnSearchResultsCleared(m_nativeCallerPointer);
    }

    public void clearSearchResults()
    {
        m_searchWidget.clearSearch();

        m_searchWidget.showResultsView(); // state to "shown", for the next time a search is done
    }

    public void onSearchResultsSelected(SearchResult searchResult) {
        SearchWidgetResult widgetResult = (SearchWidgetResult) searchResult;

        SearchWidgetViewJniMethods.OnSearchResultSelected(
                m_nativeCallerPointer,
                widgetResult.getIndex());
    }

    @Override
    public void textChanged(String newtext) {
        SearchWidgetViewJniMethods.OnSearchbarTextChanged(
                m_nativeCallerPointer,
                newtext
        );
    }

    @Override
    public void navigateTo(SearchResult navigateTo) {
        SearchWidgetResult widgetResult = (SearchWidgetResult) navigateTo;

        SearchWidgetViewJniMethods.OnSearchResultNavigationRequest(
                m_nativeCallerPointer,
                widgetResult.getIndex());
    }

    public void onSearchPerformed(String queryText,
                                  boolean clearPreviousResults,
                                  boolean isTag, String tagText,
                                  boolean tryInterior,
                                  boolean usesLocation,
                                  double latitude, double longitude, double altitude,
                                  boolean usesRadius,
                                  float radius)
    {
        QueryContext context =
            usesLocation ?
                new QueryContext(clearPreviousResults,
                                 isTag, tagText, tryInterior,
                                 latitude, longitude, altitude, radius) :
            usesRadius ?
                new QueryContext(clearPreviousResults,
                                 isTag, tagText, tryInterior,
                                 radius) :
                new QueryContext(clearPreviousResults,
                        isTag, tagText, tryInterior);

        m_searchWidget.getSearchResults(queryText, context);
    }

    public boolean onMenuOptionSelected(final String text, final Object context) {
        MenuIndexPath indexPath = (MenuIndexPath) context;

        SearchWidgetViewJniMethods.SelectedItem(m_nativeCallerPointer, text, indexPath.m_section, indexPath.m_item);
        return true;
    }



    public void populateData(
            final long nativeCallerPointer,
            final String[] optionNames,
            final int[] optionSizes,
            final String[] childJsons) {

        if(m_hasPopulatedData==true){
            updateData(optionNames,optionSizes,childJsons);
            return;
        }

        m_hasPopulatedData = true;

        m_searchWidget.clearMenu();

        MenuGroup menuGroup = null;

        List<String> options = Arrays.asList(optionNames);
        int jsonChildIndex = 0;

        for (int optionIndex = 0; optionIndex < options.size(); optionIndex++)
        {
            String optionStartsGroup = getFromJson(optionNames[optionIndex], "groupStart");
            String optionName = getFromJson(optionNames[optionIndex], "name");

            if (optionIndex == 0 || optionStartsGroup != null && optionStartsGroup.equals("Y")) {
                menuGroup = new MenuGroup();
                m_searchWidget.addMenuGroup(menuGroup);
                m_menuGroups.put(optionName,menuGroup);
            }

            int optionSizeWithoutHeader = optionSizes[optionIndex]-1;

            MenuIndexPath optionIndexPath = new MenuIndexPath(optionIndex, 0);

            MenuOption menuOption = new MenuOption(optionName, optionIndexPath, this);
            m_menuOptions.put(optionName,menuOption);

            menuGroup.addOption(menuOption);

            jsonChildIndex++;

            for (int childIndex = 0; childIndex < optionSizeWithoutHeader; ++childIndex) {
                String childJson = childJsons[jsonChildIndex];
                addChildToMenuOption(childIndex,optionIndex,childJson,menuOption);
                jsonChildIndex++;
            }
        }
    }

    public void updateData(
            final String[] optionNames,
            final int[] optionSizes,
            final String[] childJsons){

        List<String> options = Arrays.asList(optionNames);
        int jsonChildIndex = 0;

        for (int optionIndex = 0; optionIndex < options.size(); optionIndex++) {

            int optionSizeWithoutHeader = optionSizes[optionIndex]-1;

            String optionName = getFromJson(optionNames[optionIndex], "name");
            MenuIndexPath optionIndexPath = new MenuIndexPath(optionIndex, 0);

            MenuOption menuOption = m_menuOptions.get(optionName);

            jsonChildIndex++;

            if(menuOption == null) {
                menuOption = new MenuOption(optionName, optionIndexPath, this);
                m_menuOptions.put(optionName,menuOption);
            }

            menuOption.removeAllChildren();
            for (int childIndex = 0; childIndex < optionSizeWithoutHeader; ++childIndex) {
                String childJson = childJsons[jsonChildIndex];
                addChildToMenuOption(childIndex,optionIndex,childJson,menuOption);
                jsonChildIndex++;
            }

        }
    }

    private void addChildToMenuOption(int childIndex, int optionIndex,String childJson, MenuOption menuOption){
        MenuIndexPath indexPath = new MenuIndexPath(optionIndex, childIndex);
        String name = getFromJson(childJson, "name");
        String iconName = getFromJson(childJson, "icon");
        int iconNumber = TagResources.getIconForResourceName(m_activity, iconName);
        MenuChild child = new MenuChild(name, iconNumber, indexPath, this);
        menuOption.addChild(child);
    }


    private String getFromJson(String jsonString, String tag) {
        try {
            JSONObject json = new JSONObject(jsonString);
            String name = json.getString(tag);
            return name;
        } catch (Exception e) {
            Log.e("SearchWidgetView", String.format("Unable to parse %s from group JSON: %s", tag, e.toString()));
            return null;
        }
    }

    public void ViewLayoutChanged() {
        final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);

        final float viewHeight = m_view.getHeight();

        float y = m_view.getY();

        float inactiveY = -viewHeight;

        m_viewAnimator.setActivePos(y);
        m_viewAnimator.setInactivePos(inactiveY);

        m_view.setY(inactiveY);
    }

    public void animateOnScreen() {
        m_viewAnimator.animateToActive(m_stateChangeAnimationTimeMilliseconds);
    }

    public void animateOffScreen() {
        m_searchWidget.hideResultsView();
        m_searchWidget.closeMenu();
        m_viewAnimator.animateToInactive(m_stateChangeAnimationTimeMilliseconds);
    }

    public void animateToIntermediateOnScreenState(final float onScreenState) {
        m_searchWidget.hideResultsView();
        m_searchWidget.closeMenu();
        m_viewAnimator.animateToOnScreenState(onScreenState);
    }

    public void closeMenu() {
        m_searchWidget.hideResultsView();
        m_searchWidget.closeMenu();
        m_view.clearFocus();
    }

    private void pushControlsOfScreenIfNeeded(){

        boolean hasVisibleSearchResults = m_searchResultsAreVisible && (m_hasSearchResults || m_searchInProgress);

        boolean shouldTakeFocus = m_searchTextboxIsInFocus ||hasVisibleSearchResults || m_menuIsOpen;

        if( shouldTakeFocus )
        {
            SearchWidgetViewJniMethods.ViewPushesControlsOffscreen(m_nativeCallerPointer);
        }
        else
        {
            SearchWidgetViewJniMethods.ViewAllowsControlsOnscreen(m_nativeCallerPointer);
        }
    }

    private void setHasSearchResults(boolean hasResults){
        m_hasSearchResults = hasResults;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onFocusChange(View view, boolean inFocus) {
        if(inFocus && !m_searchTextboxIsInFocus && !(m_hasSearchResults || m_searchInProgress))
        {
            return;
        }

        m_searchTextboxIsInFocus = inFocus;
        pushControlsOfScreenIfNeeded();
    }

    //SearchResultViewListener:

    @Override
    public void onSearchResultsShown() {
        m_searchResultsAreVisible = true;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onSearchResultsHidden() {
        m_searchResultsAreVisible = false;
        pushControlsOfScreenIfNeeded();
    }

    //MenuViewListener:

    @Override
    public void onMenuClosed() {
        m_menuIsOpen = false;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onMenuOpened() {
        m_menuIsOpen = true;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onMenuChildSelected(MenuChild menuChild) {

    }

    @Override
    public void onMenuOptionExpanded(MenuOption menuOption) {

    }

    @Override
    public void onMenuOptionCollapsed(MenuOption menuOption) {

    }

    @Override
    public void onMenuOptionSelected(MenuOption menuOption) {

    }

    //SearchQueryModelListener:
    @Override
    public void onSearchQueryStarted(SearchQuery query)
    {
        m_searchInProgress = true;
        pushControlsOfScreenIfNeeded();

        m_searchProvider.showNavButtons(true);
    }

    @Override
    public void onSearchQueryCompleted(SearchQuery query, List<SearchProviderQueryResult> results)
    {

        m_searchInProgress = false;
        pushControlsOfScreenIfNeeded();
    }

    @Override
    public void onSearchQueryCancelled(SearchQuery query)
    {
        m_searchInProgress = false;
        pushControlsOfScreenIfNeeded();
    }
}