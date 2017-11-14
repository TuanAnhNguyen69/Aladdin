using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace MapEditor
{
    class Object
    {
        private int id;    //để chia quad tree đồng thời phân biệt các object với nhau
        private String name;    //Name of Object
        private Rectangle rec;  //lưu vị trí, kích thước của object
        private String type;    //Lưu loại object
        private Bitmap image;   //Image đại diện cho object trên map

        public int Id
        {
            get { return id; }
            set { id = value; }
        }

        public String Name
        {
            get { return name; }
            set { name = value; }
        }

        public Rectangle Rec
        {
            get { return rec; }
            set { rec = value; }
        }
        public int Y
        {
            get { return rec.Y; }
            set { rec.Y = value; }
        }
        public String Type
        {
            get { return type; }
            set { type = value; }
        }
        public Bitmap Image
        {
            get { return image; }
            set { image = value; }
        }

        public Object(String _name,Rectangle _rec)
        {
            Name = _name;
            Rec = _rec;
            initImage();
            Type = " ";
        }

        public Object(String _name, Rectangle _rec, String _type)
        {
            Name = _name;
            Rec = _rec;
            initImage();
            this.Type = _type;
        }

        private void initImage()
        {

            image = new Bitmap(rec.Width, rec.Height);
            switch (name)
            {
                case "Fat_Sword_Guard":
                    image = global::MapEditor.Properties.Resources.Fat_Sword_Guard;
                    break;
                case "Fat_Throw_Sword":
                    image = global::MapEditor.Properties.Resources.Fat_Throw_Sword;
                    break;
                case "Thin_Sword_Guard":
                    image = global::MapEditor.Properties.Resources.Thin_Sword_Guard;
                    break;
                case "Thin_Throw_Sword":
                    image = global::MapEditor.Properties.Resources.Thin_Throw_Sword;
                    break;
                case "Throw_pot":
                    image = global::MapEditor.Properties.Resources.Throw_pot;
                    break;
                case "Bottle_Enemy":
                    image = global::MapEditor.Properties.Resources.Bottle_Enemy;
                    break;
                case "apple":
                    image = global::MapEditor.Properties.Resources.apple;
                    break;
                case "Heart":
                    image = global::MapEditor.Properties.Resources.Heart;
                    break;
                case "Item":
                    image = global::MapEditor.Properties.Resources.Item;
                    break;
                case "Genie":
                    image = global::MapEditor.Properties.Resources.Genie;
                    break;
                case "Lamp":
                    image = global::MapEditor.Properties.Resources.Lamp;
                    break;
                case "Peddler1":
                    image = global::MapEditor.Properties.Resources.Peddler1;
                    break;
                case "Camel":
                    image = global::MapEditor.Properties.Resources.Camel;
                    break;
                case "Peddler2":
                    image = global::MapEditor.Properties.Resources.Peddler2;
                    break;

            }
        }        
    }
}
