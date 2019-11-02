using System;
using System.Diagnostics;
using System.Runtime.Remoting.Messaging;
using System.Threading;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media.Imaging;

namespace ImageEdit
{
    public class ImageOpPipe : ConnectPipe
    {
        public void OpenFile(string fileName, Action<BitmapImage> connectReceive)
        {
            Exc(Cmd.OpenFile, fileName);
            var process = Process.GetCurrentProcess();
            ConnectReceive = connectReceive;
        }

        public Action<BitmapImage> ConnectReceive { get; set; }

        protected override void Revice(BitmapImage bitmap)
        {
            ConnectReceive(bitmap);
        }
    }
}