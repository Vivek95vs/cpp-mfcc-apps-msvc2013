using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Sidd3iCollisionWrapper;

namespace addcshar
{
    class Program
    {
        static void Main(string[] args)
        {

            Sidd3iCollision RDF = new Sidd3iCollision();
            RDF.coll(0, 0, 0, 0, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0);
           

        }
    }
}
