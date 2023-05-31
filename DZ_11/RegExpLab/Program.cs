using System;
using System.Text.RegularExpressions;
using System.IO;
using System.Text;

namespace RegExpLab
{
    class Program
    {
        static void Main(string[] args)
        {
            string text;
            try
            {
                using (StreamReader sr = new StreamReader("CreateDB.sql"))
                {
                    text = sr.ReadToEnd();
                    Console.WriteLine(text.Length);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка чтения файла: \" CreateDB.sql\"\n{0}", ex);
                return;
            }

            text = Regex.Replace(text, @"GO", "");
            text = Regex.Replace(text, @"SET .{0,} ON", "");
            text = Regex.Replace(text, @"\[", "");
            text = Regex.Replace(text, @"\]", "");
            text = Regex.Replace(text, @"IDENTITY\(1,1\)", "AUTO_INCREMENT");
            text = Regex.Replace(text, @"timestamp", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP");
            text = Regex.Replace(text, @"CONSTRAINT", "PRIMARY KEY");
            text = Regex.Replace(text, @"PRIMARY KEY CLUSTERED", "PRIMARY KEY");
            text = Regex.Replace(text, @"WITH PAD_INDEX = OFF", "");
            text = Regex.Replace(text, @"WITH STATISTICS_NORECOMPUTE = OFF", "");
            text = Regex.Replace(text, @"WITH IGNORE_DUP_KEY = OFF", "");
            text = Regex.Replace(text, @"WITH ALLOW_ROW_LOCKS = ON", "PRIMARY KEY");
            text = Regex.Replace(text, @"ON \[PRIMARY\]", "PRIMARY KEY");
            text = Regex.Replace(text, @"UNIQUE NONCLUSTERED", " UNIQUE KEY");
            text = Regex.Replace(text, @"WITH PAD_INDEX = OFF", "");
            text = Regex.Replace(text, @"WITH STATISTICS_NORECOMPUTE = OFF", "");
            text = Regex.Replace(text, @"WITH IGNORE_DUP_KEY = OFF", "");
            text = Regex.Replace(text, @"WITH ALLOW_ROW_LOCKS = ON", "");
            text = Regex.Replace(text, @"WITH ALLOW_PAGE_LOCKS = ON", "");
            text = Regex.Replace(text, @"ON \[PRIMARY\]", "UNIQUE KEY");
            text = Regex.Replace(text, @"ON \[PRIMARY\].{1,}", ";");
            text = Regex.Replace(text, @"uniqueidentifier", "char(32)");
            text = Regex.Replace(text, @"xml", "text");
            text = Regex.Replace(text, @"ntext", "text");
            text = Regex.Replace(text, @"nvarchar\(max\)", "text");
            text = Regex.Replace(text, @"image", "BLOB");
            text = Regex.Replace(text, @"varbinary\(max\)", "BLOB");

            try
            {
                using (StreamWriter sw = new StreamWriter(".\\text.txt", false, Encoding.UTF8))
                {
                    sw.Write(text);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ошибка сохранений в файл: \"{0}\"\n{1}", "text.txt", ex);
                return;
            }


            Console.WriteLine(text);
            Console.ReadKey();
        }
    }
}
