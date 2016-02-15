﻿using ExampleApp;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class SettingsMenuView : MenuView
    {
        private double m_screenWidthPx;
        private double m_mainContainerOnScreenWidthPx;
        private TextBox m_editText;
        private MenuListAdapter m_adapter;
        private bool m_isFirstLayout = true;
        private Grid m_mainContainer;
        private Grid m_dragTabContainer;
        private bool m_isMouseDown = false;
        private static readonly ResourceDictionary genericResourceDictionary;
        private CustomAppAnimation m_mainContainerAnim;
        private ControlClickHandler m_menutItemHandler;

        static SettingsMenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SettingsMenuView), new FrameworkPropertyMetadata(typeof(SettingsMenuView)));
            var uri = new Uri("/ExampleAppWPF;component/Colours.xaml", UriKind.Relative);
            genericResourceDictionary = (ResourceDictionary)Application.LoadComponent(uri);
        }

        public SettingsMenuView(IntPtr nativeCallerPointer) : base(nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.SizeChanged += PerformLayout;
            mainWindow.MainGrid.Children.Add(this);
            Loaded += SettingsMenuView_Loaded;
        }

        private void SettingsMenuView_Loaded(object sender, RoutedEventArgs e)
        {
            PerformLayout(sender, null);
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_list = (ListBox)GetTemplateChild("SecondaryMenuItemList");
            m_menutItemHandler = new ControlClickHandler(OnSelectionChanged, m_list);

            m_dragTabView = (Button)GetTemplateChild("SecondaryMenuDragTabView");
            m_dragTabContainer = (Grid)GetTemplateChild("DragTabParentGrid");

            m_dragTabView.Click += OnIconClick;

            m_mainContainer = (Grid)GetTemplateChild("SecondaryMenuViewListContainer");
            m_mainContainerAnim = new CustomAppAnimation(m_mainContainer as FrameworkElement);
            m_mainContainer.RenderTransformOrigin = new Point(0.5, 0.5);

            m_menuAnimations.Add(m_mainContainerAnim);

            var fadeInItemStoryboard = ((Storyboard)Template.Resources["FadeInNewItems"]).Clone();
            var fadeOutItemStoryboard = ((Storyboard)Template.Resources["FadeOutOldItems"]).Clone();

            m_adapter = new MenuListAdapter(false, m_list, fadeInItemStoryboard, fadeOutItemStoryboard, "SettingsMenuItemPanel");

            PerformLayout(null, null);
        }

        private void OnIconClick(object sender, RoutedEventArgs e)
        {
            MenuViewCLIMethods.ViewClicked(m_nativeCallerPointer);
        }

        private void OnSelectionChanged(object sender, MouseEventArgs e)
        {
            if (IsAnimating() || m_adapter.IsAnimating())
            {
                (sender as ListBox).SelectedItem = null;
                return;
            }

            var item = m_list.SelectedItem as SubMenuListItem;
            if (item != null)
            {
                var position = m_adapter.Children
                    .Select((_t, _i) => Tuple.Create(_t, _i))
                    .Where(_t => _t.Item1.Heading == item.Heading)
                    .Single().Item2;

                int sectionIndex = m_adapter.GetSectionIndex(position);
                int childIndex = m_adapter.GetItemIndex(position);

                MenuViewCLIMethods.SelectedItem(m_nativeCallerPointer, sectionIndex, childIndex);
            }
        }

        public override void AnimateToClosedOnScreen()
        {
            base.AnimateToClosedOnScreen();
            m_mainContainer.Visibility = Visibility.Hidden;
        }

        public override void AnimateToOpenOnScreen()
        {
            base.AnimateToOpenOnScreen();
            m_mainContainer.Visibility = Visibility.Visible;
        }

        private void PerformLayout(object sender, SizeChangedEventArgs e)
        {
            var currentPosition = RenderTransform.Transform(new Point(0.0, 0.0));
            double onScreenState = (currentPosition.X - m_mainContainerAnim.m_offscreenPos.X) / (m_mainContainerAnim.m_openPos.X - m_mainContainerAnim.m_offscreenPos.X);
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            m_screenWidthPx = mainWindow.MainGrid.ActualWidth;
            var screenWidthPy = mainWindow.MainGrid.ActualHeight;

            double dragTabWidthPx = m_dragTabView.ActualWidth;

            m_mainContainerOffscreenOffsetXPx = -m_dragTabView.Margin.Right;
            double mainContainerWidthPx = m_mainContainer.ActualWidth;
            m_mainContainerOnScreenWidthPx = mainContainerWidthPx - m_mainContainerOffscreenOffsetXPx;

            m_mainContainerAnim.m_widthHeight.X = mainContainerWidthPx + dragTabWidthPx;
            m_mainContainerAnim.m_offscreenPos.X = (m_screenWidthPx / 2) + (m_mainContainerAnim.m_widthHeight.X / 2);
            m_mainContainerAnim.m_closedPos.X = m_mainContainerAnim.m_offscreenPos.X - (dragTabWidthPx + 32);
            m_mainContainerAnim.m_openPos.X = m_mainContainerAnim.m_offscreenPos.X - m_mainContainerAnim.m_widthHeight.X;

            double layoutX = m_mainContainerAnim.m_offscreenPos.X;

            if (!m_isFirstLayout)
            {
                layoutX = onScreenState * (m_mainContainerAnim.m_openPos.X - m_mainContainerAnim.m_offscreenPos.X) + m_mainContainerAnim.m_offscreenPos.X;
            }

            RenderTransform = new TranslateTransform(layoutX, currentPosition.Y);
            m_isFirstLayout = false;
        }


        protected override void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap)
        {
            m_adapter.SetData(groups, groupsExpandable, groupToChildrenMap);

            var itemsSource = new List<SubMenuListItem>();

            var detailsList = groupToChildrenMap[groups[0]];

            foreach (var str in detailsList)
            {
                var jObject = JObject.Parse(str);
                var item = new SubMenuListItem(str, 0);
                itemsSource.Add(item);
            }

            m_list.ItemsSource = itemsSource;

            if (m_list.DataContext != m_adapter)
            {
                m_list.DataContext = m_adapter;
            }

        }
    }
}
