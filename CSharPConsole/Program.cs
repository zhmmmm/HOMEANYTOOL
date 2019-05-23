using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CSharPConsole
{
    class Program
    {

        //--------------DLL接口定义-----------
        [DllImport("CPLUSPLUSDLL.dll", EntryPoint = "classInit", CharSet =

        CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern int classInit(ref int clsPoint);

        [DllImport("CPLUSPLUSDLL.dll", EntryPoint = "CallClass", CharSet = CharSet.Auto,

        CallingConvention = CallingConvention.StdCall)]
        public static extern int add(ref int clsPoint, int p1, int p2);
        // DLL中的类实例指针
        private static int _clsPoint = 0;

        static void Main(string[] args)
        {
            _clsPoint = classInit(ref _clsPoint);

            int n = add(ref _clsPoint, 123, 123);
            Console.Write("result: " + n);

            Console.Read();
        }



        //静态调用
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
