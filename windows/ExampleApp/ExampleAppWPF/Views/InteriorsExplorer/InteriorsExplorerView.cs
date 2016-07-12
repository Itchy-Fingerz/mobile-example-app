﻿using ExampleApp;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    public class InteriorsExplorerView : ControlBase
    {
        private IntPtr m_nativeCallerPointer;
        private Slider m_floorSlider;
        private TickBarVerticalWithLabels m_sliderTickBar;
        private TextBlock m_floorName;
        private Button m_dismissButton;
        private Grid m_floorPanel;
        private Grid m_detailsPanel;
        
        private int m_selectedFloorIndex;
        private double m_panelOffscreenOffsetX;
        private double m_stateChangeAnimationTimeMilliseconds = 200.0;
        private bool m_dragInProgress = false;
        private string[] m_floorShortNames = new string[] {};

        private const float DefaultOffscreenOffsetX = 100.0f;

        private int FloorCount { get { return m_floorShortNames.Length; } }
        private bool FloorSelectionEnabled { get { return FloorCount > 1; } }

        static InteriorsExplorerView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(InteriorsExplorerView), new FrameworkPropertyMetadata(typeof(InteriorsExplorerView)));            
        }

        public InteriorsExplorerView(IntPtr nativeCallerPointer)
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            mainWindow.MainGrid.Children.Add(this);
            m_nativeCallerPointer = nativeCallerPointer;
        }

        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();

            m_panelOffscreenOffsetX = DefaultOffscreenOffsetX;

            m_floorSlider = GetTemplateChild("FloorSlider") as Slider;
            m_floorSlider.ValueChanged += OnSliderValueChanged;

            m_floorSlider.ApplyTemplate();

            m_sliderTickBar = GetTickBar(m_floorSlider);

            var sliderThumb = GetThumb(m_floorSlider);

            sliderThumb.DragStarted += OnSliderDragStarted;
            sliderThumb.DragCompleted += OnSliderDragCompleted;

            m_floorName = (TextBlock)GetTemplateChild("FloorName");

            m_dismissButton = (Button)GetTemplateChild("DismissButton");
            m_dismissButton.Click += OnClickDismiss;

            m_floorPanel = (Grid)GetTemplateChild("FloorPanel");

            m_detailsPanel = (Grid)GetTemplateChild("DetailsPanel");

            m_detailsPanel.Opacity = 0.0f;
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));
            m_floorPanel.RenderTransform = new TranslateTransform(m_panelOffscreenOffsetX, currentPosition.Y);

            SetTouchEnabled(false);
            Hide();
        }

        private static Thumb GetThumb(Slider slider)
        {
            var track = slider.Template.FindName("PART_Track", slider) as Track;
            return track == null ? null : track.Thumb;
        }

        private static TickBarVerticalWithLabels GetTickBar(Slider slider)
        {
            var tickBar = slider.Template.FindName("SliderTickBar", slider);
            return tickBar == null ? null : tickBar as TickBarVerticalWithLabels;
        }

        private void OnClickDismiss(object sender, RoutedEventArgs e)
        {
            InteriorsExplorerCLIMethods.Dismiss(m_nativeCallerPointer);
        }

        public void Destroy()
        {
            MainWindow mainWindow = (MainWindow)Application.Current.MainWindow;
            if (mainWindow != null)
            {
                mainWindow.MainGrid.Children.Remove(this);
            }
        }
        public void UpdateFloors(string[] floorShortNames, int currentlySelectedFloorIndex)
        {
            System.Diagnostics.Debug.Assert(floorShortNames != null, "floorShortNames cannot be null");
            m_floorShortNames = floorShortNames;

            m_sliderTickBar.TickLabels = string.Join(",", floorShortNames);

            m_selectedFloorIndex = currentlySelectedFloorIndex;

            m_floorSlider.Minimum = 0;
            m_floorSlider.Maximum = FloorCount - 1;
            m_floorSlider.Value = m_selectedFloorIndex;
            UpdateFloorSliderTagFromValue();
        }
        public void SetFloorName(string name)
        {
            if (m_floorName != null)
            {
                m_floorName.Text = name;
            }
        }

        public void SetSelectedFloor(int floorIndex)
        {
            m_selectedFloorIndex = floorIndex;
        }

        public void SetOnScreenStateToIntermediateValue(float transitionParam)
        {
            double newX = CalcPanelX(transitionParam);
            m_detailsPanel.Opacity = transitionParam;
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));
            m_floorPanel.RenderTransform = new TranslateTransform(newX, currentPosition.Y);
        }

        private double CalcPanelX(double t)
        {
            t = Math.Min(Math.Max(t, 0.0), 1.0);
            double newX = m_panelOffscreenOffsetX - t * m_panelOffscreenOffsetX;
            return newX;
        }

        public void SetFullyOnScreen()
        {
            AnimateTo(1.0f);
        }

        public void SetFullyOffScreen()
        {
            AnimateTo(0.0f);
        }
        private void AnimateTo(float t)
        {
            if (t > 0.0f)
            {
                Visibility = Visibility.Visible;
            }

            var storyboard = new Storyboard();
            var currentPosition = m_floorPanel.RenderTransform.Transform(new Point(0.0, 0.0));


            
            var floorPanelAnimation = new DoubleAnimation();
            floorPanelAnimation.From = currentPosition.X;
            floorPanelAnimation.To = CalcPanelX(FloorSelectionEnabled ? t : 0.0f);
            floorPanelAnimation.Duration = new Duration(TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds));

            var transform = new TranslateTransform(currentPosition.X, currentPosition.Y);
            m_floorPanel.RenderTransform = transform;
            transform.BeginAnimation(TranslateTransform.XProperty, floorPanelAnimation);

            var detailsPanelAnimation = new DoubleAnimation();
            detailsPanelAnimation.From = m_detailsPanel.Opacity;
            detailsPanelAnimation.To = t;
            detailsPanelAnimation.Duration = new Duration(TimeSpan.FromMilliseconds(m_stateChangeAnimationTimeMilliseconds));

            detailsPanelAnimation.Completed += Storyboard_Completed;

            m_detailsPanel.BeginAnimation(OpacityProperty, detailsPanelAnimation);


            //var testAnim = new DoubleAnimation();
            //testAnim.From = 1.0;
            //testAnim.To = 0.0;
            //testAnim.AutoReverse = true;
            //testAnim.RepeatBehavior = RepeatBehavior.Forever;
            //testAnim.Duration = new Duration(TimeSpan.FromSeconds(1.0));

            //m_floorSlider.Background.BeginAnimation(Brush.OpacityProperty, testAnim);

            //testAnim.CurrentTimeInvalidated += delegate (object sender, EventArgs e)
            //{
            //    //var value = (double)(testAnim.GetValue(OpacityProperty));
            //    var test = m_floorSlider.Background.Opacity;
            //    m_floorSlider.Background.Opacity = test;
            //    m_floorSlider.Background.InvalidateProperty(OpacityProperty);
            //    m_floorSlider.InvalidateVisual();
            //};


            //            m_floorSlider.Background = m_testBrush;
            //m_floorSlider.BeginAnimation(OpacityProperty, testAnim);
            //m_testBrush.Opacity = 0.3;


        }

        private void Storyboard_Completed(object sender, EventArgs e)
        {
            Visibility = (m_detailsPanel.Opacity == 0.0) ? Visibility.Hidden : Visibility.Visible;
        }

        public void SetTouchEnabled(bool enabled)
        {
            m_floorPanel.IsHitTestVisible = enabled;
            m_detailsPanel.IsHitTestVisible = enabled;
        }

        public void SetFloorPanelEnabled(bool enabled)
        {
            m_floorPanel.IsHitTestVisible = enabled;
        }

        public void Show()
        {
            Visibility = Visibility.Visible;
        }
        public void Hide()
        {
            Visibility = Visibility.Hidden;
        }

        private void OnSliderDragStarted(object sender, DragStartedEventArgs e)
        {
            m_dragInProgress = true;
            SetFloorSelectionDrag(m_floorSlider.Value);
        }

        private void OnSliderDragCompleted(object sender, DragCompletedEventArgs e)
        {
            m_dragInProgress = false;

            var floorIndex = (int)Math.Round(m_floorSlider.Value);
            m_floorSlider.Value = floorIndex;

            InteriorsExplorerCLIMethods.SelectFloor(m_nativeCallerPointer, floorIndex);
        }

        private void OnSliderValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (m_dragInProgress)
            {
                SetFloorSelectionDrag(e.NewValue);
            }
        }

        private void SetFloorSelectionDrag(double sliderValue)
        {
            double dragParam = Math.Min(1.0, sliderValue / m_floorSlider.Maximum);
            InteriorsExplorerCLIMethods.SetFloorSelectionDrag(m_nativeCallerPointer, dragParam);
            UpdateFloorSliderTagFromValue();
        }

        private void UpdateFloorSliderTagFromValue()
        {
            var floorIndex = (int)Math.Round(m_floorSlider.Value);
            m_floorSlider.Tag = m_floorShortNames[floorIndex];

        }
    }
}
