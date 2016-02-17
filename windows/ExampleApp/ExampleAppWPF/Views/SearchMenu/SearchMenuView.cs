﻿using ExampleApp;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace ExampleAppWPF
{
    public class SearchMenuView : MenuView
    {
        private TextBox m_editText;
        private MenuListAdapter m_adapter;
        private Grid m_searchBox;

        private ListBox m_resultsList;
        private MenuListAdapter m_resultListAdapter;
        private Grid m_resultsSpinner;
        private TextBlock m_resultsCount;
        private Button m_resultsClearButton;
        private ScrollViewer m_menuOptionsView;
        private ScrollViewer m_resultsOptionsView;
        private FrameworkElement m_searchArrow;

        private Grid m_resultsCountContainer;

        private string m_defaultEditText;

        private ControlClickHandler m_menuListClickHandler;
        private ControlClickHandler m_resultsListClickHandler;

        private Storyboard m_searchInputOpen;
        private Storyboard m_searchInputClose;

        private Storyboard m_searchInputTextOpen;
        private Storyboard m_searchInputTextClose;

        private Storyboard m_searchArrowOpen;
        private Storyboard m_searchArrowClosed;

        private bool m_searchPerformed;

        static SearchMenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SearchMenuView), new FrameworkPropertyMetadata(typeof(SearchMenuView)));
        }

        public SearchMenuView(IntPtr nativeCallerPointer) : base(nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);

            Loaded += MainWindow_Loaded;
            mainWindow.SizeChanged += PerformLayout;

            m_searchPerformed = false;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            PerformLayout(sender, null);
        }

        private new void PerformLayout(object sender, SizeChangedEventArgs e)
        {
            var screenWidth = m_mainWindow.MainGrid.ActualWidth;
            var totalWidth = m_mainContainer.ActualWidth + m_menuIcon.ActualWidth;

            m_onScreenPos = -(screenWidth / 2);
            m_offScreenPos = -(screenWidth / 2) - (totalWidth / 2);

            base.PerformLayout(sender, e);

            m_menuOptionsView.MaxHeight = m_mainWindow.MainGrid.ActualHeight * 0.75;
            m_resultsOptionsView.MaxHeight = m_mainWindow.MainGrid.ActualHeight * 0.55;
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_menuOptionsView = (ScrollViewer)GetTemplateChild("MenuOptionsView");
            m_resultsOptionsView = (ScrollViewer)GetTemplateChild("ResultsMenuOptionsView");
            m_resultsSpinner = (Grid)GetTemplateChild("SearchResultsSpinner");
            m_resultsCount = (TextBlock)GetTemplateChild("SearchResultCount");
            m_resultsCountContainer = (Grid)GetTemplateChild("SearchResultCountContainer");
            m_menuViewContainer = (Grid)GetTemplateChild("SearchMenuViewContainer");
            m_backgroundRectangle = (Rectangle)GetTemplateChild("BackgroundRect");
            m_searchBox = (Grid)GetTemplateChild("SearchBox");
            m_searchArrow = (FrameworkElement)GetTemplateChild("SearchArrow");

            m_resultsClearButton = (Button)GetTemplateChild("SearchClear");
            m_resultsClearButton.Click += OnResultsClear;

            m_list = (ListBox)GetTemplateChild("SecondaryMenuItemList");
            m_menuListClickHandler = new ControlClickHandler(OnMenuListItemSelected, m_list);
            m_list.PreviewMouseWheel += OnMenuScrollWheel;

            m_resultsList = (ListBox)GetTemplateChild("SearchResultsList");
            m_resultsListClickHandler = new ControlClickHandler(OnResultsListItemsSelected, m_resultsList);
            m_resultsList.PreviewMouseWheel += OnResultsMenuScrollWheel;

            m_menuIcon = (Button)GetTemplateChild("SecondaryMenuDragTabView");
            m_menuIconGrid = (Grid)GetTemplateChild("SearchIconGrid");

            m_menuIcon.Click += OnIconClick;

            m_editText = (TextBox)GetTemplateChild("SearchInputBox");
            m_editText.KeyDown += OnKeyDown;
            m_editText.GotFocus += OnSearchBoxSelected;
            m_editText.LostFocus += OnSearchBoxUnSelected;
            m_editText.TextChanged += OnSearchBoxTextChanged;
            m_defaultEditText = m_editText.Text;

            m_mainContainer = (Grid)GetTemplateChild("SerchMenuMainContainer");

            var fadeInItemStoryboard = ((Storyboard)Template.Resources["FadeInNewItems"]).Clone();
            var fadeOutItemStoryboard = ((Storyboard)Template.Resources["FadeOutOldItems"]).Clone();

            m_openSearchIconAnim = ((Storyboard)Template.Resources["OpenSearchViewIcon"]).Clone();
            m_closeSearchIconAnim = ((Storyboard)Template.Resources["CloseSearchViewIcon"]).Clone();

            m_openSearchContainerAnim = ((Storyboard)Template.Resources["OpenSearchContainer"]).Clone();
            m_closeSearchContainerAnim = ((Storyboard)Template.Resources["CloseSearchContainer"]).Clone();

            m_openBackgroundRect = ((Storyboard)Template.Resources["OpenBackgroundRect"]).Clone();
            m_closeBackgroundRect = ((Storyboard)Template.Resources["CloseBackgroundRect"]).Clone();

            m_searchInputOpen = ((Storyboard)Template.Resources["OpenSearchInputBox"]).Clone();
            m_searchInputClose = ((Storyboard)Template.Resources["CloseSearchInputBox"]).Clone();

            m_searchInputTextOpen = ((Storyboard)Template.Resources["OpenSearchInputBoxText"]).Clone();
            m_searchInputTextClose = ((Storyboard)Template.Resources["CloseSearchInputBoxText"]).Clone();

            m_searchArrowOpen = ((Storyboard)Template.Resources["OpenSearchArrow"]).Clone();
            m_searchArrowClosed  = ((Storyboard)Template.Resources["CloseSearchArrow"]).Clone();

            m_adapter = new MenuListAdapter(false, m_list, fadeInItemStoryboard, fadeOutItemStoryboard, "SubMenuItemPanel");
            m_resultListAdapter = new MenuListAdapter(false, m_resultsList, fadeInItemStoryboard, fadeOutItemStoryboard, "SearchResultPanel");
        }

        private void OnSearchBoxTextChanged(object sender, TextChangedEventArgs e)
        {
            if (m_editText.Text?.Length > 0 && m_editText.Text != m_defaultEditText)
            {
                m_resultsClearButton.Visibility = Visibility.Visible;
            }
            else
            {
                m_resultsClearButton.Visibility = Visibility.Hidden;
            }
        }

        private void OnMenuScrollWheel(object sender, MouseWheelEventArgs e)
        {
            m_menuOptionsView.ScrollToVerticalOffset(m_menuOptionsView.VerticalOffset - e.Delta);
            e.Handled = true;
        }

        private void OnResultsMenuScrollWheel(object sender, MouseWheelEventArgs e)
        {
            m_resultsOptionsView.ScrollToVerticalOffset(m_resultsOptionsView.VerticalOffset - e.Delta);
            e.Handled = true;
        }

        private void OnMenuListItemSelected(object sender, MouseEventArgs e)
        {
            if (IsAnimating() || m_adapter.IsAnimating())
            {
                (sender as ListBox).SelectedItem = null;
                return;
            }

            var item = m_list.SelectedItem as MenuListItem;
            if (item != null)
            {
                int position = m_adapter.Children.IndexOf(item);

                int sectionIndex = m_adapter.GetSectionIndex(position);
                int childIndex = m_adapter.GetItemIndex(position);

                MenuViewCLIMethods.SelectedItem(m_nativeCallerPointer, sectionIndex, childIndex);

                ClearSearchResultsListBox();
                if (m_editText.Text != "" && m_editText.Text != m_defaultEditText)
                {
                    m_resultsClearButton.Visibility = Visibility.Visible;
                }
            }
        }

        private void OnResultsListItemsSelected(object sender, MouseEventArgs e)
        {
            if (m_resultsList.SelectedItems?.Count > 0)
            {
                SearchMenuViewCLIMethods.HandleSearchItemSelected(m_nativeCallerPointer, m_resultsList.SelectedIndex);
                m_searchPerformed = true;
            }
        }

        private void OnSearchBoxUnSelected(object sender, RoutedEventArgs e)
        {
            if( m_editText.Text.Replace(" ", null) == string.Empty)
            {
                m_editText.Text = m_defaultEditText;
            }
        }

        private void OnSearchBoxSelected(object sender, RoutedEventArgs e)
        {
            if(m_editText.Text == m_defaultEditText)
            {
                m_editText.Text = string.Empty;
            }
        }

        private void ClearSearchResultsListBox()
        {
            m_resultListAdapter.ResetData();

            m_resultListAdapter.CollapseAll();
            m_resultsList.DataContext = null;
            m_resultsList.ItemsSource = null;

            m_resultsCountContainer.Visibility = Visibility.Hidden;
            m_resultsClearButton.Visibility = Visibility.Hidden;
            m_searchArrow.Visibility = Visibility.Hidden;
        }

        private void OnResultsClear(object sender, RoutedEventArgs e)
        {
            if(m_resultsList.Items?.Count > 0)
            {
                SearchMenuViewCLIMethods.OnSearchCleared(m_nativeCallerPointer);
            }
            else
            {
                m_editText.Text = string.Empty;
            }

            ClearSearchResultsListBox();
        }

        private void OnIconClick(object sender, RoutedEventArgs e)
        {
            MenuViewCLIMethods.ViewClicked(m_nativeCallerPointer);
        }

        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                string queryText = m_editText.Text;

                if (queryText.Length > 0)
                {
                    SearchMenuViewCLIMethods.PerformedSearchQuery(m_nativeCallerPointer, queryText);

                    m_resultsSpinner.Visibility = Visibility.Visible;
                    m_resultsClearButton.Visibility = Visibility.Hidden;

                    m_searchPerformed = true;
                }
            }
        }

        public void SetSearchSection(string category, string[] searchResults)
        {
            if(!m_searchPerformed)
            {
                return;
            }

            m_resultListAdapter.ResetData();

            var groups = new List<string>(searchResults.Length);
            var groupsExpandable = new List<bool>(searchResults.Length);
            var groupToChildren = new Dictionary<string, List<string>>();

            var itemsSource = new List<SearchMenuListItem>();

            foreach (var str in searchResults)
            {
                var jObject = JObject.Parse(str);
                var item = new SearchMenuListItem();
                item.Name = jObject["name"].Value<string>();
                item.Details = jObject["details"].Value<string>();

                JToken iconStringToken;
                var iconString = jObject.TryGetValue("icon", out iconStringToken) ? iconStringToken.Value<string>() : "misc";
                item.Icon = new System.Windows.Media.Imaging.BitmapImage(ViewHelpers.MakeUriForImage(string.Format("icon1_{0}.png", iconString)));
                itemsSource.Add(item);

                groups.Add(str);
                groupsExpandable.Add(false);
                groupToChildren.Add(str, new List<string>());
            }

            m_resultListAdapter.SetData(groups, groupsExpandable, groupToChildren);

            m_resultsList.DataContext = m_resultListAdapter;

            m_resultsList.ItemsSource = itemsSource;

            m_resultsSpinner.Visibility = Visibility.Hidden;
            m_resultsClearButton.Visibility = Visibility.Visible;
            m_searchArrow.Visibility = Visibility.Visible;

            m_searchPerformed = false;
        }

        public override void AnimateToClosedOnScreen()
        {
            if (m_openState != MENU_CLOSED && m_openState != MENU_CLOSING)
            {
                if(m_isOffScreen)
                {
                    m_searchBox.Visibility = Visibility.Hidden;
                }
                else
                {
                    m_searchBox.Visibility = Visibility.Visible;

                    m_searchInputClose.Begin(m_searchBox);
                    m_searchInputTextClose.Begin(m_editText);
                    m_searchArrowClosed.Begin(m_searchArrow);
                }

                base.AnimateToClosedOnScreen();
            }
        }

        public override void AnimateToOpenOnScreen()
        {
            if (m_openState != MENU_OPEN && m_openState != MENU_OPENING)
            {
                m_searchBox.Visibility = Visibility.Visible;

                m_searchInputOpen.Begin(m_searchBox);
                m_searchInputTextOpen.Begin(m_editText);
                m_searchArrowOpen.Begin(m_searchArrow);

                base.AnimateToOpenOnScreen();
            }
        }

        public void DisableEditText()
        {
            Dispatcher.Invoke(() =>
            {
                m_editText.IsEnabled = false;
            });
        }
        public void EnableEditText()
        {
            Dispatcher.Invoke(() =>
            {
                m_editText.IsEnabled = true;
            });
        }

        public void SetEditText(string text, bool isCategory)
        {
            m_editText.Text = text;
        }

        public void SetSearchResultCount(int count)
        {
            if(count > 0)
            {
                m_resultsCount.Text = count.ToString();
                m_resultsCountContainer.Visibility = Visibility.Visible;
            }
            else
            {
                m_resultsCountContainer.Visibility = Visibility.Hidden;
            }
        }

        protected override void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap)
        {
            m_adapter.SetData(groups, groupsExpandable, groupToChildrenMap);

            m_list.DataContext = m_adapter;
        }
    }
}
