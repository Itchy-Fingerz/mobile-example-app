﻿using System;
using System.Windows;
using ExampleApp;
using System.Windows.Controls;
using System.Diagnostics;
using System.Windows.Input;

namespace ExampleAppWPF
{
    class AboutPageView : Control
    {
        private IntPtr m_nativeCallerPointer;
        private MainWindow m_currentWindow;

        private TextBlock m_aboutTextView;
        private Button m_closeButton;
        private FrameworkElement m_mainContainer;


        static AboutPageView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(AboutPageView), new FrameworkPropertyMetadata(typeof(AboutPageView)));
        }

        public AboutPageView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_currentWindow = (MainWindow)Application.Current.MainWindow;
            m_currentWindow.MainGrid.Children.Add(this);

            Visibility = Visibility.Hidden;
        }

        private DependencyObject CheckAndGetProperty(string name)
        {
            var prop = GetTemplateChild(name);
            Debug.Assert(prop != null, "Property cannot be found!!");
            return prop;
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
            m_aboutTextView = CheckAndGetProperty("AppText") as TextBlock;
            m_closeButton = CheckAndGetProperty("CloseButton") as Button;

            m_closeButton.Click += OnCloseClicked;
            m_mainContainer = (FrameworkElement)GetTemplateChild("MainContainer");

            m_mainContainer.MouseDown += OnContainerMouseDown;
        }

        private void OnContainerMouseDown(object sender, MouseButtonEventArgs e)
        {
            e.Handled = true;
        }

        private void OnCloseClicked(object sender, RoutedEventArgs e)
        {
            AboutPageCLI.CloseButtonClicked(m_nativeCallerPointer);
        }

        public void Destroy()
        {
            m_currentWindow.MainGrid.Children.Remove(this);
        }

        public void DisplayContent(string content)
        {
            m_aboutTextView.Text = content;
        }

        public void OpenAboutPage()
        {
            Visibility = Visibility.Visible;
            m_currentWindow.DisableInput();
        }

        public void DismissAboutPage()
        {
            Visibility = Visibility.Hidden;
            m_currentWindow.EnableInput();
        }
    }
}
