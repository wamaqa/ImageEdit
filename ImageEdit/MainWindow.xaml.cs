using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.MemoryMappedFiles;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;

namespace ImageEdit
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private ImageOpPipe m_connectPipe;
        public MainWindow()
        {
            InitializeComponent();
            m_connectPipe = new ImageOpPipe();
        }

        private void MainWindow_OnLoaded(object sender, RoutedEventArgs e)
        {
            m_connectPipe.Start(this);
           
        }

        private void MenuOpenFile_OnClick(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Title = "打开文件";
            openFileDialog.Filter = "图像文件(*.bmp, *.jpg, *.png) | *.bmp; *.jpg; *.png| 所有文件(*.*) | *.*";
            if (openFileDialog.ShowDialog() == true)
            {
                m_connectPipe.OpenFile(openFileDialog.FileName, ConnectReceive);
                string fileName = openFileDialog.FileName;
                IntPtr intPtr = new IntPtr();
            }
        }

        private void MainWindow_OnClosed(object sender, EventArgs e)
        {
            m_connectPipe.Close();
        }

        private void ConnectReceive(BitmapImage image)
        {
            Image.Source = null;
            Image.Source = image;
        }

        private void MenuSaveAsFile_OnClick(object sender, RoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void Savefile_OnClick(object sender, RoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void SliderExposure_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            m_connectPipe.SetExposure(SliderExposure.Value, SliderContrast.Value, SliderBrightness.Value, ConnectReceive);
        }
    }

 
}
