using System;
using SourceAFIS.Simple;

namespace ConsoleApplication1
{
    class Program
    {
        private static readonly string HexString = "5D 69 2D A1 43 2F AA 82 2F 6F 48 2F 43 49 35 96 45 37 AF 81 48 B0 BF 48 96 48 48 +" +
                                                   "5D 89 4A 9C 43 4D 7C 6A 4D 63 6A 4D 19 45 4F 73 8B 50 91 42 54 85 6B 57 6B AA 58 +" +
                                                   "86 B2 58 7D 70 59 36 82 5B 8C 57 5E 94 9C 5F 73 71 61 61 66 64 4C 9C 69 97 9B 6F +" +
                                                   "A5 9D 70 33 B9 72 50 96 74 92 58 7D 27 59 7E 9D 59 80 66 93 83 4A 56 86 8E 56 90 +" +
                                                   "3D 74 9A 3A 76";

        private static readonly string HexString1 = "464D52002032300000000144000000C0010C00C800C80100000063014087000B66000000";
        //private static readonly string HexString2 = "464D520020323000000000F00000012C019000C500C5010000105B01406E00156E000000";

        private static readonly string HexStringFromFmrFile =
          "46 4D 52 00 20 32 30 00 00 00 00 DE 00 00 01 2C 01 90 00 C5 00 C5 01 00 00 10 5B 20 40 87 00 0B 66 00 80 B5 00 3B 67 00 40 71 00 17 6C 00 40 76 00 34 6D 00 80 A0 00 4B E2 00 80 8F 00 5B 61 00 40 5A 00 61 70 00 80 41 00 65 FC 00 40 7D 00 82 67 00 40 35 00 75 86 00 40 AA 00 A9 DD 00 80 6B 00 A0 E0 00 80 5C 00 95 71 00 40 45 00 93 F5 00 40 2C 00 C0 9A 00 40 9C 00 F3 58 00 40 36 00 CE 13 00 80 46 00 DB E3 00 40 2D 00 E5 13 00 40 66 00 F4 5A 00 40 AF 01 1E 65 00 40 96 01 1A 61 00 80 55 01 08 E0 00 80 A2 01 3B 71 00 40 51 01 0C CF 00 40 37 01 0A AD 00 80 48 01 04 C8 00 40 7A 01 3B 78 00 40 6A 01 30 74 00 40 A7 01 51 77 00 80 5D 01 5F 0C 00 40 99 01 67 81 00 00 00";

        private static readonly string HexFromTemplate =
            "464D520020323000000000DE0000012C019000C500C5010000105B204087000B660080B5003B6700407100176C00407600346D0080A0004BE200808F005B6100405A0061700080410065FC00407D0082670040350075860040AA00A9DD00806B00A0E000805C0095710040450093F500402C00C09A00409C00F35800403600CE1300804600DBE300402D00E51300406600F45A0040AF011E65004096011A610080550108E00080A2013B71004051010CCF004037010AAD0080480104C800407A013B7800406A0130740040A701517700805D015F0C004099016781000000";

        static void Main(string[] args)
        {
            //var t = HexString2.Split().Select(s => Convert.ToByte(s, 16)).ToArray();
            var t = StringToByteArray(HexFromTemplate);

            var afisEngine = new AfisEngine();
            var enrollPrint = new Fingerprint { AsIsoTemplate = t };
            var enrollPerson = new Person(enrollPrint);
            var verifyPrint = new Fingerprint { AsIsoTemplate = t };
            var verifyPerson = new Person(verifyPrint);

            var matchScore = afisEngine.Verify(enrollPerson, verifyPerson);

            Console.WriteLine("Template length: {0}", enrollPrint.Template.Length);
            Console.WriteLine("Matching Score: {0}", matchScore);
            Console.WriteLine("Finished");
            Console.ReadLine();
        }
        public static byte[] StringToByteArray(string hex)
        {
            Console.WriteLine("Hex String Length: {0}", hex.Length);
            int NumberChars = hex.Length;
            byte[] bytes = new byte[NumberChars / 2];
            for (int i = 0; i < NumberChars; i += 2)
                bytes[i / 2] = Convert.ToByte(hex.Substring(i, 2), 16);
            return bytes;
        }
    }
}
