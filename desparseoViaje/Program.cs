using System;
using System.Globalization;
using System.Xml;

namespace desparseoViaje
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                XmlDocument xmlDoc = new XmlDocument();
                xmlDoc.Load(@"viaje.xml");
                XmlNodeList pointNodes = xmlDoc.SelectNodes("/trkseg/trkpt");
                foreach (XmlNode pointNode in pointNodes)
                {
                    XmlNode latNode = pointNode.SelectSingleNode("@lat");
                    XmlNode lonNode = pointNode.SelectSingleNode("@lon");
                    XmlNode timeNode = pointNode.SelectSingleNode("time");
                    DateTime dt = dt = DateTime.ParseExact(timeNode.InnerText, "yyyy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture);
                    Console.WriteLine("medicion({0},puntoGps({1},{2})),", Date2Seconds(dt), latNode.InnerText, lonNode.InnerText);

                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            static long Date2Seconds(DateTime timestamp)
            {
                return (long)timestamp.Subtract(new DateTime(1970, 1, 1)).TotalSeconds;
            }
        }
    }
}
