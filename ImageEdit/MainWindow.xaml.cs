using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
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
        [DllImport("User32.dll", EntryPoint = "PostThreadMessage")]
        private static extern int PostThreadMessage( int idThread, int Msg, IntPtr wParam, IntPtr lParam);
        private Process m_process;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void MainWindow_OnLoaded(object sender, RoutedEventArgs e)
        {
            //m_process = Process.Start(".\\ImageServer.exe");
            m_process = Process.GetProcessesByName("ImageServer").FirstOrDefault();
        }

        private void MenuOpenFile_OnClick(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Title = "打开文件";
            openFileDialog.Filter = "png文件|*.png";
            if (openFileDialog.ShowDialog() == true)
            {
                string fileName = openFileDialog.FileName;
                PostThreadMessage(m_process.Threads[0].Id, 0x0400 + 50, new IntPtr(12), new IntPtr(23));
            }
        }

        private void MainWindow_OnClosed(object sender, EventArgs e)
        {
            m_process.Close();
        }
    }
}
