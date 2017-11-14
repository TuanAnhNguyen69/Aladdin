using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
namespace MapEditor
{
    class WorldMap
    {
        String fileName;    //Name Of file Map
        int width, height;  //Kích thước file ảnh map(pixel)
        //Map
        public int cols;  
        public int rows;
        public int[,] setArr;  //ma trận tile map
        public List<Bitmap> tilesList;  //List tile map
        private List<Object> listObject;    //List Obj game
        private List<Rectangle> listRec;    //List hình chữ nhật va chạm. khi xét vc nền, thay vì xét va chạm 
        //QuadTree                          //từng viên gạch ta dùng một hình chữ nhật bao quanh các viên gạch trên cùng một dòng để xét va chạm
        Quadtree quadtree;
        List<int[]> listQuadtree;   //Chứa danh sách quad node. mỗi phần tử trong list lưu thông tin id, vị trí, kích thước và dánh sách id của object thuộc node đó

        internal List<Object> ListObject
        {
            get { return listObject; }
            set { listObject = value; }
        }

        internal List<Rectangle> ListRec
        {
            get { return listRec; }
            set { listRec = value; }
        }

        //Lấy hình chữ nhật va chạm trong listRec của map, hình chữ nhật có chứa điểm x,y
        public Rectangle getRectangleAtPos(int x, int y)
        {
            if(listRec.Count > 0)
                foreach (Rectangle rc in ListRec)
                {
                    if (rc.Contains(new Point(x, y)))
                        return rc;
                }
            return new Rectangle(0, 0, 0, 0);
        }
        //Lấy object trong listObject của map, vị trí object có chứa điểm x,y
        public Object getObjectsAtPos(int x, int y)
        {
            if (ListObject.Count > 0)
                foreach (Object obj in ListObject)
                {
                    if (obj.Rec.Contains(new Point(x, y))) 
                        return obj;
                }
            return null;
        }

        public WorldMap()
        {
            tilesList = new List<Bitmap>();
            listObject = new List<Object>();
            ListRec = new List<Rectangle>();
            listQuadtree = new List<int[]>();
        }
        //Hàm tao quad tree, hàm này được gọi trước khi save map
        private Quadtree CreateQuadTree()
        {
            listQuadtree.Clear();
            quadtree = new Quadtree(0,1, new Rectangle(0, 0, width, height));
            foreach (Object o in listObject)
                quadtree.Insert(o); //Thêm object vào quadtree
            quadtree.GetListObject(listQuadtree);   //Lấy danh sách quad node
            return quadtree;
        }

        public void LoadMap(String dir)
        {
            int tileCount = 0;
            Rectangle rc = new Rectangle();

            fileName = dir.Split('.')[0];
            using (XmlReader reader = XmlReader.Create(fileName + ".tmx"))
            {
                //Read Map Info
                reader.ReadToFollowing("map");
                reader.MoveToAttribute("width");
                cols = int.Parse(reader.Value);
                reader.MoveToAttribute("height");
                rows = int.Parse(reader.Value);

                //Read Map Collison Rec
                reader.Read();
                if (!reader.IsStartElement()) reader.Read();
                if (reader.LocalName.CompareTo("objectgroup") == 0)
                {
                    while (reader.Read())
                    {
                        if (reader.LocalName.CompareTo("objectgroup") == 0) break;
                        if (reader.LocalName.CompareTo("object") == 0)
                        {
                            reader.MoveToAttribute("x");
                            rc.X = int.Parse(reader.Value);
                            reader.MoveToAttribute("y");
                            rc.Y = int.Parse(reader.Value);
                            reader.MoveToAttribute("width");
                            rc.Width = int.Parse(reader.Value);
                            reader.MoveToAttribute("height");
                            rc.Height = int.Parse(reader.Value);
                            listRec.Add(rc);
                        }
                    }

                    //Read Map Object
                    reader.ReadToFollowing("objectgroup");
                    while (reader.Read())
                    {
                        if (reader.LocalName.CompareTo("objectgroup") == 0) break;
                        if (reader.LocalName.CompareTo("object") == 0)
                        {
                            reader.MoveToAttribute("name");
                            string sname = reader.Value;
                            reader.MoveToAttribute("type");
                            string type = reader.Value;
                            reader.MoveToAttribute("x");
                            rc.X = int.Parse(reader.Value);
                            reader.MoveToAttribute("y");
                            rc.Y = int.Parse(reader.Value);
                            reader.MoveToAttribute("width");
                            rc.Width = int.Parse(reader.Value);
                            reader.MoveToAttribute("height");
                            rc.Height = int.Parse(reader.Value);
                            listObject.Add(new Object(sname, rc, type));
                        }
                    }

                    //Read Map Set Array
                    reader.ReadToFollowing("layer");
                    reader.MoveToAttribute("tilecount");
                    tileCount = int.Parse(reader.Value);
                    reader.ReadToFollowing("data");
                    setArr = new int[rows, cols];
                    for (int i = 0; i < rows; i++)
                    {
                        for (int j = 0; j < cols; j++)
                        {
                            reader.Read();
                            if (!reader.IsStartElement()) reader.Read();
                            if (reader.LocalName.CompareTo("tile") == 0)
                            {
                                reader.MoveToAttribute("gid");
                                setArr[i, j] = int.Parse(reader.Value);
                            }
                        }
                    }
                }
                else
                {
                    reader.MoveToAttribute("tilecount");
                    tileCount = int.Parse(reader.Value);
                    reader.ReadToFollowing("data");
                    setArr = new int[rows, cols];
                    for (int i = 0; i < rows; i++)
                    {
                        for (int j = 0; j < cols; j++)
                        {
                            reader.Read();
                            if (!reader.IsStartElement()) reader.Read();
                            if (reader.LocalName.CompareTo("tile") == 0)
                            {
                                reader.MoveToAttribute("gid");
                                setArr[i, j] = int.Parse(reader.Value);
                            }
                        }
                    }
                }
            }

            //Read bitmap
            string tiles_dir = dir.Split('.')[0] + ".bmp";
            Bitmap background = new Bitmap(tiles_dir);
            for (int k = 0; k < tileCount; k++)
            {
                Rectangle r2 = new Rectangle(k % 10 * 32, k / 10 * 32, 32, 32);
                Bitmap b = background.Clone(r2, background.PixelFormat);
                tilesList.Add(b);
            }
        }

        public void SaveMap(int _width, int _height)
        {
            int id = 0;
            string idObj = "";
            foreach (Object obj in listObject)
                obj.Id = id++;
            width = height = Math.Max(_width, _height);
            CreateQuadTree();

            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            using (XmlWriter writer = XmlWriter.Create(fileName + ".tmx", settings))
            {
                writer.WriteStartDocument();
                writer.WriteStartElement("map");
                writer.WriteAttributeString("width", cols.ToString());
                writer.WriteAttributeString("height", rows.ToString());
                writer.WriteAttributeString("tilewidth", "32");
                writer.WriteAttributeString("tileheight", "32");

                //Coliision Layer
                writer.WriteStartElement("objectgroup");
                writer.WriteAttributeString("name", "Collision");
                foreach (Rectangle rc in ListRec)
                {
                    writer.WriteStartElement("object");
                    writer.WriteAttributeString("x", rc.X.ToString());
                    writer.WriteAttributeString("y", rc.Y.ToString());
                    writer.WriteAttributeString("width", rc.Width.ToString());
                    writer.WriteAttributeString("height", rc.Height.ToString());
                    writer.WriteEndElement();
                }
                writer.WriteEndElement();

                //Object Layer
                writer.WriteStartElement("objectgroup");
                writer.WriteAttributeString("name", "MoveObject");
                foreach (Object o in listObject)
                {
                    writer.WriteStartElement("object");
                    writer.WriteAttributeString("name", o.Name);
                    writer.WriteAttributeString("id", o.Id.ToString());
                    writer.WriteAttributeString("type", o.Type);
                    writer.WriteAttributeString("x", o.Rec.X.ToString());
                    writer.WriteAttributeString("y", o.Rec.Y.ToString());
                    writer.WriteAttributeString("width", o.Rec.Width.ToString());
                    writer.WriteAttributeString("height", o.Rec.Height.ToString());
                    writer.WriteEndElement();
                }
                writer.WriteEndElement();

                //QuadTree
                writer.WriteStartElement("QuadTree");
                writer.WriteAttributeString("name", "QuadTree");
                foreach (int[] a in listQuadtree)
                {
                    idObj = "";
                    writer.WriteStartElement("QuadNode");
                    writer.WriteAttributeString("NodeID", a[0].ToString());
                    writer.WriteAttributeString("x", a[1].ToString());
                    writer.WriteAttributeString("y", a[2].ToString());
                    writer.WriteAttributeString("width", a[3].ToString());
                    writer.WriteAttributeString("height", a[4].ToString());
                    for (int i = 5; i < a.Length; i++ )
                    {
                        idObj += a[i] + " ";
                    }
                    writer.WriteAttributeString("id", idObj);
                    writer.WriteEndElement();
                }
                writer.WriteEndElement();

                //Map layer
                writer.WriteStartElement("layer");
                writer.WriteAttributeString("name", "Map");
                writer.WriteAttributeString("tilecount", tilesList.Count.ToString());
                writer.WriteStartElement("data");
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        writer.WriteStartElement("tile");
                        writer.WriteAttributeString("gid", setArr[i, j].ToString());
                        writer.WriteEndElement();
                    }
                }

                writer.WriteEndElement();
                writer.WriteEndElement();

                writer.WriteEndElement();
                writer.WriteEndDocument();
            }
        }        
    }
}
