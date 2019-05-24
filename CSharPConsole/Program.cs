using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CSharPConsole
{
    class BASS
    {
        [DllImport("CPLUSPLUSDLL.dll", EntryPoint = "InitAudioEngine", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern bool InitAudioEngine();//函数名可以不匹配
        [DllImport("CPLUSPLUSDLL.dll", EntryPoint = "LoadMusics", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern int LoadMusic(byte[] FileName);//函数名可以不匹配

        [DllImport("CPLUSPLUSDLL.dll")]
        public static extern bool PlayMusics(int HStream);//函数名一定要匹配
        [DllImport("CPLUSPLUSDLL.dll")]
        public static extern bool SetVolume(int V);//函数名一定要匹配
        [DllImport("CPLUSPLUSDLL.dll", SetLastError = true, CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern bool PauseMusics(int HStream);//函数名一定要匹配
        [DllImport("CPLUSPLUSDLL.dll")]
        public static extern bool UninstallAudioEngine();//函数名一定要匹配
        public int GetInstanse()
        {
            return 1;
        }
        public void F()
        {
            InitAudioEngine();
            PlayMusics(LoadMusic(Encoding.ASCII.GetBytes("Music.mp3")));
        }
        //指针
        public void F(ref int var)
        {
            InitAudioEngine();
            PauseMusics(LoadMusic(Encoding.ASCII.GetBytes("Music.mp3")));
        }
    }
    class Program
    {
        //--------------DLL接口定义-----------
        [DllImport("CPLUSPLUSDLL.dll", EntryPoint = "classInit", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern int classInit(ref int clsPoint);

        [DllImport("CPLUSPLUSDLL.dll", EntryPoint = "CallClass", CharSet = CharSet.Auto,CallingConvention = CallingConvention.StdCall)]
        public static extern int add(ref int clsPoint, int p1, int p2);
        [DllImport("CPLUSPLUSDLL.dll")]
        public static extern int Add(int H);
        // DLL中的类实例指针
        private static int _clsPoint = 0;
        //==================================================

        //UIntPtr
        //System.Text.Encoding.ASCII.GetBytes("M.mp3")


        [DllImport("CPLUSPLUSDLL.dll", EntryPoint = "InitAudioEngine", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern bool InitAudioEngine();//函数名可以不匹配
        [DllImport("CPLUSPLUSDLL.dll", EntryPoint = "LoadMusics", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern int LoadMusic(byte[] FileName);//函数名可以不匹配

        [DllImport("CPLUSPLUSDLL.dll")]
        public static extern bool PlayMusics(int HStream);//函数名一定要匹配
        [DllImport("CPLUSPLUSDLL.dll")]
        public static extern bool SetVolume(int V);//函数名一定要匹配
        [DllImport("CPLUSPLUSDLL.dll", SetLastError = true, CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern bool PauseMusics(int HStream);//函数名一定要匹配
        [DllImport("CPLUSPLUSDLL.dll")]
        public static extern bool UninstallAudioEngine();//函数名一定要匹配


        public static int HStream;
        //c++ long == c# int
        //c++ 句柄 == c# UIntPtr
        //c++ char == c# byte
        //c++ 类指针 == c# ref var //c++返回的是一级指针 
        //这样通过 ref var 就可作为一个指向一个类对象的指针
        //注意以上CPlusPlusDLL解决方案的事例 //非常有意思,由于内容太多需要时间封装
        //今天 2019.5.24.23.53.00
        //可以把c++的句柄作为c#的UIntPtr或者是int 实验试是成功的
        //注意音频的名字格式,不能有空格的Name和不能是中文,特殊情况下建议用绝对路径
        //注意注意注意       =============》c++ char ================byte
        /// <summary>
        /// c++导出时是C的方式,所有没有函数的重载,在c#总需要额外封装
        /// c++ 直接导出类c#是查不到符号的,需要在类的外部的到类的指针再通过这个类对象的指针进行(ref var)调用
        /// 在c#中的调用方法已经算是一个单列了,那么在c++中就不用导出一个单列类(这算是一个扩展)
        /// 
        /// 强烈建议直接导出函数,至于重载就在c#中来写(还是有一点c++的味道 ,换汤不换药)
        /// 
        /// </summary>

        static BASS Bass = new BASS();
        static void Main(string[] args)
        {
            _clsPoint = classInit(ref _clsPoint);
            int n = add(ref _clsPoint, 123, 123);
            Console.WriteLine("result: " + n);
            Console.WriteLine(Add(0));

            Bass.F();

            //InitAudioEngine();
            //SetVolume(100);
            //HStream = LoadMusic(Encoding.ASCII.GetBytes("Music.mp3"));//一定要转码
            //PlayMusics(HStream);
            //Console.ReadKey();
            //PauseMusics(HStream);
            //Console.ReadKey();
            //PlayMusics(HStream);


            Console.ReadKey();
            UninstallAudioEngine();
        }






        //静态调用
        //c# 调用基于x64的dll 必须用release版本调用
        //必须有 __stdcall
        //[DllImport("CPLUSPLUSDLL.dll")]
        //public static extern int add(int p1);
        //static void Main(string[] args)
        //{
        //    int p = add(123);
        //    Console.Write(p);
        //    Console.Read();
        //}

    }
}
