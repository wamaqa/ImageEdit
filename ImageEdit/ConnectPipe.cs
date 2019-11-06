using System;
using System.Diagnostics;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interop;
using System.Windows.Media.Imaging;
using Newtonsoft.Json;

namespace ImageEdit
{
    public abstract class ConnectPipe
    {
        private const int Command = 0x0401;

        private MemoryMappedFile m_mappedWrite;
        private MemoryMappedFile m_mappedRead;


        [DllImport("User32.dll", EntryPoint = "PostThreadMessage")]
        private static extern int PostThreadMessage(int idThread, int Msg, int wParam, int lParam);
        private Process m_process;
        private HwndSource hwndSource;
        public void Start(System.Windows.Media.Visual visual)
        {
            //string path = System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName;
            //string p = Path.GetDirectoryName(path);
            //m_process = Process.Start(string.Format("{0}\\ImageServer.exe", p));
            m_process = Process.GetProcessesByName("ImageServer").FirstOrDefault();
            m_mappedWrite = MemoryMappedFile.CreateOrOpen("ImageEdit", 1024);
            m_mappedRead = MemoryMappedFile.CreateOrOpen("ImageServer", 8 * 1024 * 1024 * 100);
            Hwnd = Process.GetCurrentProcess().MainWindowHandle.ToInt64();
            hwndSource = HwndSource.FromHwnd(Process.GetCurrentProcess().MainWindowHandle);
            hwndSource.AddHook(Hook);
        }

        public long Hwnd { get; set; }

        private IntPtr Hook(IntPtr hwnd, int msg, IntPtr wparam, IntPtr lparam, ref bool handled)
        {
            if (msg != Command) return hwnd;
            MemoryMappedViewAccessor viewAccessor = m_mappedRead.CreateViewAccessor();
            //读取字符长度
            int size = wparam.ToInt32();
            byte[] data = new byte[wparam.ToInt64()];
            //读取字符
            long offset = viewAccessor.PointerOffset;

            FileStream file = new FileStream("D:\\a.png", FileMode.OpenOrCreate);
            file.Write(data, 0, size);
            file.Close();

            viewAccessor.ReadArray<byte>(0, data, 0, size);
            MemoryStream memory = new MemoryStream();
            memory.Write(data, 0, size);
            BitmapImage bitmap = new BitmapImage();
            bitmap.BeginInit();
            bitmap.StreamSource = memory;
            bitmap.EndInit();
            Revice(bitmap);
            return hwnd;
        }

        protected abstract void Revice(BitmapImage bitmap);

        public void Close()
        {
            m_process?.Close();
        }

        public void Post(PostData data)
        {
            MemoryMappedViewAccessor viewAccessor = m_mappedWrite.CreateViewAccessor();
            if (viewAccessor.CanWrite)
            {
                viewAccessor.Write(0, ref data);
            }
            PostThreadMessage(m_process.Threads[0].Id, Command, 0, 0);

        }

        public void Exc(int cmd, params object[] param)
        {
            PostData postData = new PostData();
            postData.Command = cmd;
            postData.DataType = 1;
            postData.Data = param;
            postData.Source = Hwnd;
            Encoding defaultCode = Encoding.Unicode;
            var bytes = defaultCode.GetBytes(JsonConvert.SerializeObject(postData).ToCharArray());
            Encoding.Convert(Encoding.Unicode, Encoding.ASCII, bytes);
            MemoryMappedViewAccessor viewAccessor = m_mappedWrite.CreateViewAccessor();
            if (viewAccessor.CanWrite)
            {
                viewAccessor.WriteArray(0, bytes, 0, bytes.Length);
            }
            PostThreadMessage(m_process.Threads[0].Id, Command, 0, 0);
        }

    }


    public enum DataType
    {
        stringData = 1,
    }

    /// <summary>
    /// 提交数据
    /// </summary>
    [StructLayout(LayoutKind.Auto, CharSet = CharSet.Unicode)]
   public  struct PostData
    {
        /// <summary>
        /// 命令ID
        /// </summary>
        public int Command { set; get; }
        /// <summary>
        /// 数据类型
        /// </summary>
        public int DataType { set; get; }
        /// <summary>
        /// 数据大小
        /// </summary>
        public int Size { set; get; }
        public long Source { set; get; }
        /// <summary>
        /// 提交数据
        /// </summary>
        public object[] Data { set; get; }
    }
}