using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Xml;

namespace TileMap
{
    public partial class TileMap : Form
    {
        PictureBox pb_background;
        PictureBox pb_tiles;

        Bitmap background;
        Bitmap appWorkSpace;
        Bitmap tiles;

        string mapLocation = "";
        int cols;
        int rows;
        int[,] setArr;
        public List<Bitmap> tilesList;

        public TileMap()
        {
            InitializeComponent();

            pb_background = new PictureBox();            
            pb_tiles = new PictureBox();            

            tilesList = new List<Bitmap>();

            pnBackGround.Controls.Add(pb_background);
            pnTileSet.Controls.Add(pb_tiles);
        }

        private void btnOpenFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog dg = new OpenFileDialog();
            dg.Filter = "Image Files (bmp, jpg, png)|*.bmp;*.jpg;*.png";
            if (dg.ShowDialog() == DialogResult.OK)
            {
                if (tilesList.Count > 0)    //sau khi mở file thành công cần xóa đi tilesList của map trước
                    tilesList.Clear();
                mapLocation = dg.FileName;
                lbFileName.Text = dg.FileName;
                this.background = new Bitmap(mapLocation);
                cols = background.Width / 32;       //lấy chiều rộng, cao của map chia cho độ rộng, cao của một tile map(32) thì được kích thước mảng
                rows = background.Height / 32;
                this.setArr = new int[rows, cols];

                DoWork();   //cắt ảnh
                Complete(); //vẽ lại map        
            }            
        }

        private void DoWork()
        {
            try
            {
                int k = 0;  //Vị trí tile map trong tilesList
                bool has = false;   //Kiểm tra xem tile map cắt ra từ map có tồn tại trong tilesList hay chưa
                for (int row = 0; row < rows; row++)
                {
                    for (int col = 0; col < cols; col++)
                    {
                        has = false;
                        Rectangle r = new Rectangle(col * 32, row * 32, 32, 32);
                        Bitmap pro = background.Clone(r, background.PixelFormat);

                        foreach (Bitmap b in tilesList)
                            if (CompareBitmaps(pro, b))
                            {
                                has = true;
                                k = tilesList.IndexOf(b);
                                setArr[row, col] = k;
                                break;
                            }
                        if (!has)
                        {
                            tilesList.Add(pro);
                            k = tilesList.IndexOf(pro);
                            setArr[row, col] = k;
                        }
                    }
                }

            }
            catch (Exception)
            {
                throw;
            }
        }

        private bool CompareBitmaps(Bitmap leftBitmap, Bitmap rightBitmap)
        {
            #region Optimized code for performance
            int bytes = leftBitmap.Width * leftBitmap.Height * (Image.GetPixelFormatSize(leftBitmap.PixelFormat) / 8);  //lấy số byte của bit map
            bool result = true;
            //Ta không thể thao tác trên ảnh bit map mà cần phải lockbit thành bitmap data mới thao tác được
            BitmapData bmd1 = leftBitmap.LockBits(new Rectangle(0, 0, leftBitmap.Width - 1, leftBitmap.Height - 1), ImageLockMode.ReadOnly, leftBitmap.PixelFormat);
            BitmapData bmd2 = rightBitmap.LockBits(new Rectangle(0, 0, rightBitmap.Width - 1, rightBitmap.Height - 1), ImageLockMode.ReadOnly, rightBitmap.PixelFormat);
            //Khởi tạo 2 mảng byte để so sánh
            byte[] b1bytes = new byte[bytes];
            byte[] b2bytes = new byte[bytes];
            //copy bitmap 1 vào mảng byte b1bytes từ byte số 0 tới byte cuối cùng bytes.
            //Tương tự bitmap 2
            Marshal.Copy(bmd1.Scan0, b1bytes, 0, bytes);
            Marshal.Copy(bmd2.Scan0, b2bytes, 0, bytes);
            //Duyệt mảng và so sánh
            for (int n = 0; n <= bytes - 1; n++)
            {
                if (b1bytes[n] != b2bytes[n])
                {
                    result = false;
                    break;
                }
            }
            //Sau khi so sánh ta cần unlockbits
            leftBitmap.UnlockBits(bmd1);
            rightBitmap.UnlockBits(bmd2);

            #endregion

            return result;
        }

        private void Complete()
        {
            int height = (1 + this.tilesList.Count / 10) * 32;  //số dòng * 32 ra chiều cao tilesMap
            tiles = new Bitmap(320, height);
            tiles.SetResolution(72.0F, 72.0F);
            using (Graphics g = Graphics.FromImage(tiles))
            {
                SolidBrush b = new SolidBrush(Color.FromArgb(255, 0, 255));
                g.FillRectangle(b, 0, 0, tiles.Width, tiles.Height);
            }

            foreach (Bitmap bm in tilesList)
            {
                int i = tilesList.IndexOf(bm) % 10;   //tính vị trí tiles map nằm cột nào
                int j = tilesList.IndexOf(bm) / 10;   //tính vị trí tiles map nằm hàng nào

                using (Graphics g = Graphics.FromImage(tiles))
                {
                    g.InterpolationMode = InterpolationMode.NearestNeighbor;    //Chế độ nội suy khi co lại
                    g.DrawImage(bm, i * 32, j * 32, 32, 32);
                }
            }
            pb_tiles.Size = new Size(tiles.Width, tiles.Height);
            this.pb_tiles.Image = tiles;
            Draw();
        }

        private void Draw()
        {
            appWorkSpace = new Bitmap(background.Width, background.Height);
            using (Graphics g = Graphics.FromImage(appWorkSpace))
            {
                for (int row = 0; row < rows; row++)
                {
                    for (int col = 0; col < cols; col++)
                    {
                        g.InterpolationMode = InterpolationMode.NearestNeighbor;
                        int index = setArr[row, col];
                        g.DrawImage(tilesList[index], col * 32, row * 32, 32, 32);
                    }
                }
            }
            pb_background.Size = new Size(appWorkSpace.Width, appWorkSpace.Height);
            pb_background.Image = appWorkSpace;
        }

        private void btnSaveFile_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "map files (*.tmx)|*.tmx";
            dlg.Title = "Save map";
            dlg.ShowDialog();
            if (dlg.FileName != "")
            {
                SaveMap(dlg.FileName);
            }
        }

        public void SaveMap(String dir)
        {
            string name = dir.Split('.')[0];
            tiles.Save(name + ".bmp", ImageFormat.Bmp);

            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            using (XmlWriter writer = XmlWriter.Create(name + ".tmx", settings))
            {
                writer.WriteStartDocument();
                writer.WriteStartElement("map");
                writer.WriteAttributeString("width", cols.ToString());
                writer.WriteAttributeString("height", rows.ToString());
                writer.WriteAttributeString("tilewidth", "32");
                writer.WriteAttributeString("tileheight", "32");

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
