using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

namespace MapEditor
{
    public partial class MapEditor : Form
    {
        WorldMap worldmap;  //Lưu thông tin map
        PictureBox pb_background;   //PictureBox dùng để vẽ map, giao diện làm việc chính
        int heightMap;      
        int widthMap;

        //Phần Rectangle (hình chữ nhật va chạm, xét va chạm nền)
        Point startPos;      // mouse-down position
        Point currentPos;    // current mouse position
        Rectangle tmpRec;
        Rectangle currentRec;
        bool drawing;        // busy drawing

        //Phần Object
        List<PictureBox> listObj; //Mỗi 1 picture box đại diện cho 1 object
        PictureBox selection_Obj;  //Object đang chọn để vẽ
        Object currentObj;          //Object đang được chọn trên map

        public MapEditor()
        {
            InitializeComponent();
            grbRec.Enabled = true;
            grbObject.Enabled = false;
            tabControl1.Enabled = false;
            drawing = false;
            init_ObjList();
        }
        private void init_ObjList()
        {
            listObj = new List<PictureBox>();
            listObj.Add(Fat_Sword_Guard);
            listObj.Add(Fat_Throw_Sword);
            listObj.Add(Thin_Sword_Guard);
            listObj.Add(Thin_Throw_Sword);
            listObj.Add(Throw_pot);
            listObj.Add(Bottle_Enemy);

            listObj.Add(apple);
            listObj.Add(Heart);
            listObj.Add(Item);
            listObj.Add(Genie);
            listObj.Add(Lamp);

            listObj.Add(Peddler1);
            listObj.Add(Camel);
            listObj.Add(Peddler2);



            selection_Obj = listObj[0];
            foreach (PictureBox p in listObj)
                p.Click += Obj_Click;
        }
        private void Obj_Click(object sender, EventArgs e)
        {
            selection_Obj.BackColor = Color.Transparent;        
            selection_Obj = sender as PictureBox;
            selection_Obj.BackColor = SystemColors.MenuHighlight;  
        }

        private void btnOpenFile_Click(object sender, EventArgs e)
        {
            this.open();
        }
        private void open()
        {
            try
            {
                OpenFileDialog dg = new OpenFileDialog();
                dg.Filter = "Map Files (tmx)|*.tmx";
                dg.Multiselect = false;
                if (dg.ShowDialog() == DialogResult.OK)
                {
                    currentRec = new Rectangle(0, 0, 0, 0);
                    worldmap = new WorldMap();
                    worldmap.LoadMap(dg.FileName);  //Load thông tin map, hàm này được định nghĩa trong class WorldMap
                    heightMap = worldmap.rows * 32;
                    widthMap = worldmap.cols * 32;
                    this.DrawWorld(); //Hàm vẽ map
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error! \n" + ex.Message);
            }
        }
        private void DrawWorld()
        {
            pnAppWorkSpace.Controls.Clear();    //xóa sạch map trước đó
            pb_background = new PictureBox();
            pb_background.Size = new Size(widthMap, heightMap);
            pnAppWorkSpace.Controls.Add(pb_background); //dùng panel để sử dụng thanh cuộn trong trường hợp map dài

            pb_background.Paint += worldMap_Paint;      //Định nghĩa lại các sự kiện Paint, Mouse Down, Move, Up của PictureBox
            pb_background.MouseDown += WorldView_MouseDown;
            pb_background.MouseMove += WorldView_MouseMove;
            pb_background.MouseUp += WorldView_MouseUp;
        }

        private void worldMap_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;

            for (int i = 0; i < worldmap.rows; i++)
            {
                for (int j = 0; j < worldmap.cols; j++)
                {
                    g.InterpolationMode = InterpolationMode.NearestNeighbor;
                    int index = worldmap.setArr[i, j];
                    g.DrawImage(worldmap.tilesList[index], j * 32, i * 32, 32, 32);
                }
            }

            //Draw Grid
            if (cbShowGrid.Checked)
            {
                //Tạo bút vẽ dấu chấm màu xanh
                Pen p = new Pen(SystemColors.MenuHighlight, 1.0f);
                p.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot;
                for (int i = 1; i <= worldmap.rows; i++)
                    g.DrawLine(p, new Point(0, i * 32), new Point(widthMap, i * 32));
                for (int i = 0; i < worldmap.cols; i++)
                    g.DrawLine(p, new Point(i * 32, 0), new Point(i * 32, heightMap));
            }

            //Draw Objects
            foreach (Object obj in worldmap.ListObject)
            {
                g.InterpolationMode = InterpolationMode.NearestNeighbor;
                g.DrawImage(obj.Image, obj.Rec);
            }

            //Draw map collision rec
            Pen pen1 = new Pen(Color.Red, 2.0f);
            Pen pen2 = new Pen(Color.White, 2.0f);
            if (cbShowRec.Checked)
            {
                if (worldmap.ListRec.Count > 0)
                {
                    foreach (Rectangle r in worldmap.ListRec)
                    {
                        g.DrawRectangle(pen2, r.X, r.Y, r.Width, r.Height);
                    }
                }

            }

            tmpRec = getRectangle();
            if (drawing) 
                g.DrawRectangle(pen1, tmpRec);            

            //Draw selection rect
            if (currentRec.Width > 0)
            {
                Pen p2 = new Pen(Color.Yellow, 2.0f);
                g.DrawRectangle(p2, currentRec);
            }
        }

        private void WorldView_MouseMove(object sender, MouseEventArgs e)
        {
            lbLocation.Text = "X: " + e.X + "      Y: " + (heightMap - e.Y);
            //Nếu radio button rb_collison được chọn và phím Control đang nhấn
            if (rb_Collison.Checked && Control.ModifierKeys == Keys.Control)
            {
                currentPos = e.Location;    //Cập nhật vị trí hiện tại
                if (drawing)                //Cập nhật 4 text box về vị trí, kích thước của hình chữ nhật đang vẽ
                {
                    tb_RecX.Text = tmpRec.X.ToString();
                    tb_RecY.Text = (heightMap - tmpRec.Y - tmpRec.Height).ToString();
                    tb_RecW.Text = tmpRec.Width.ToString();
                    tb_RecH.Text = tmpRec.Height.ToString();
                }
            }
            //Nếu radio button rb_Objects được chọn và phím control đang được giữ
            if (rb_Objects.Checked)
            {
                if (Control.ModifierKeys == Keys.Control)
                {
                    drawing = true;         //đang vẽ
                    startPos.X = e.X - selection_Obj.Image.Width / 2;   //Tính trước vị trí
                    startPos.Y = e.Y - selection_Obj.Image.Height / 2;  //của object, thể hiện
                    currentPos.X = e.X + selection_Obj.Image.Width / 2; //lên màn hinh
                    currentPos.Y = e.Y + selection_Obj.Image.Height / 2;

                    tbPosX.Text = startPos.X.ToString();
                    tbPosY.Text = (heightMap - startPos.Y - selection_Obj.Image.Height).ToString();
                }
            }
            pb_background.Invalidate();     //Update lại map
        }

        private void WorldView_MouseDown(object sender, MouseEventArgs e)
        {
            if (rb_Collison.Checked)
            {
                if (Control.ModifierKeys == Keys.Control)
                {
                    startPos = e.Location; //Lấy vị trí bắt đầu
                    drawing = true;
                }              
                //Xóa hình chữ nhật đã click
                if(Control.ModifierKeys == Keys.Shift)
                {
                    worldmap.ListRec.Remove(worldmap.getRectangleAtPos(e.X, e.Y));
                    currentRec = new Rectangle(0, 0, 0, 0);
                }
                //Thể hiện thông tin hcn đã chọn lên các textbox
                if(Control.ModifierKeys != Keys.Shift && Control.ModifierKeys != Keys.Control)
                {
                    currentRec = worldmap.getRectangleAtPos(e.X, e.Y);
                    tb_RecX.Text = currentRec.X.ToString();
                    if (currentRec.Height == 0)
                        tb_RecY.Text = "0";
                    else
                        tb_RecY.Text = (heightMap - currentRec.Y - currentRec.Height).ToString();
                    tb_RecW.Text = currentRec.Width.ToString();
                    tb_RecH.Text = currentRec.Height.ToString();
                }
            }

            if (rb_Objects.Checked)
            {
                if (Control.ModifierKeys == Keys.Control)
                {
                    //Kiểm tra xem tại vị trí click chuột đã có object chưa
                    //Nếu có rồi thì không thêm nữa
                    currentObj = worldmap.getObjectsAtPos(e.X, e.Y);
                    if (currentObj != null)
                    {
                        if (currentObj.Name == selection_Obj.Name)
                            currentObj = null;
                        else
                            currentObj = new Object(selection_Obj.Name, tmpRec);
                    }
                    else
                    {
                        currentObj = new Object(selection_Obj.Name, tmpRec);
                    }
                }
                //Xóa object đã click
                if (Control.ModifierKeys == Keys.Shift)
                {
                    worldmap.ListObject.Remove(worldmap.getObjectsAtPos(e.X, e.Y));
                    currentObj = null;
                    tmpRec = new Rectangle(0, 0, 0, 0);
                }
                //Thể hiện thông tin object đã click lên các textbox
                if (Control.ModifierKeys != Keys.Shift && Control.ModifierKeys != Keys.Control)
                {
                    currentObj = worldmap.getObjectsAtPos(e.X, e.Y);
                    if (currentObj != null)
                    {
                        currentRec = currentObj.Rec;
                        tbPosX.Text = currentObj.Rec.X.ToString();
                        tbPosY.Text = (heightMap - currentObj.Rec.Y - currentObj.Rec.Height).ToString();
                        cb_Type.Text = currentObj.Type.ToString();
                    }
                    else
                    {
                        tbPosX.Text = "0";
                        tbPosY.Text = "0";
                    }
                }
            }
            pb_background.Invalidate(); //Update lại map
        }

        private void WorldView_MouseUp(object sender, MouseEventArgs e)
        {
            //Thêm hình chữ nhật đã vẽ vào listRec của world Map
            if (rb_Collison.Checked && Control.ModifierKeys == Keys.Control)
            {
                if (drawing)
                {
                    drawing = false;
                    if (tmpRec.Width > 0 && tmpRec.Height > 0)
                        worldmap.ListRec.Add(tmpRec);
                    currentRec = tmpRec;
                    pb_background.Invalidate();
                }
            }
            //Thêm object mới vẽ vào listObject của world Map
            if (rb_Objects.Checked && Control.ModifierKeys == Keys.Control)
            {
                drawing = false;
                if(currentObj != null)
                    worldmap.ListObject.Add(currentObj);
                currentRec = tmpRec;
                pb_background.Invalidate();
            }
        }

        private Rectangle getRectangle()
        {
            return new Rectangle(
                Math.Min(startPos.X, currentPos.X),
                Math.Min(startPos.Y, currentPos.Y),
                Math.Abs(startPos.X - currentPos.X),
                Math.Abs(startPos.Y - currentPos.Y));
        }

        private void cbShowGrid_CheckedChanged(object sender, EventArgs e)
        {
            if (pb_background != null)
                pb_background.Invalidate();
        }

        private void cbShowRec_CheckedChanged(object sender, EventArgs e)
        {
            if (pb_background != null)
                pb_background.Invalidate();
        }

        private void tb_RecX_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                UpdateRec();                
            }
        }

        private void tb_RecY_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                UpdateRec();
            }
        }

        private void tb_RecW_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                UpdateRec();
            }
        }

        private void tb_RecH_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                UpdateRec();                
            }
        }
        private void tbPosX_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                UpdateObject();
            }
        }

        private void tbPosY_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                UpdateObject();
            }
        }

        private void cb_Type_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdateObject();
        }

        private void rb_Collison_CheckedChanged(object sender, EventArgs e)
        {
            drawing = false;
            grbRec.Enabled = true;
            grbObject.Enabled = false;
            tabControl1.Enabled = false;
        }

        private void rb_Objects_CheckedChanged(object sender, EventArgs e)
        {
            drawing = false;
            grbRec.Enabled = false;
            grbObject.Enabled = true;
            tabControl1.Enabled = true;
        }

        private void UpdateRec()
        {
            if (int.Parse(tb_RecW.Text) > 0 && int.Parse(tb_RecH.Text) > 0 && currentRec.Width > 0)
            {
                worldmap.ListRec.Remove(worldmap.getRectangleAtPos(currentRec.X, currentRec.Y));
                currentRec.X = int.Parse(tb_RecX.Text);
                currentRec.Y = (heightMap - int.Parse(tb_RecY.Text) - int.Parse(tb_RecH.Text));
                currentRec.Width = int.Parse(tb_RecW.Text);
                currentRec.Height = int.Parse(tb_RecH.Text);
                worldmap.ListRec.Add(currentRec);
                if (pb_background != null)
                    pb_background.Invalidate();
            }
        }

        private void UpdateObject()
        {   
            if(currentObj != null)
            {
                worldmap.ListObject.Remove(worldmap.getObjectsAtPos(currentRec.X, currentRec.Y));
                currentRec.X = int.Parse(tbPosX.Text);
                currentRec.Y = (heightMap - int.Parse(tbPosY.Text) - currentObj.Rec.Height);
                currentObj.Rec = currentRec;
                currentObj.Type = cb_Type.Text;
                if (currentObj != null)
                    worldmap.ListObject.Add(currentObj);
                if (pb_background != null)
                    pb_background.Invalidate();
            }
        }

        private void btnSaveFile_Click(object sender, EventArgs e)
        {
            try {
                worldmap.SaveMap(widthMap, heightMap);
                MessageBox.Show("Save OK");
            }
            catch(Exception ex)
            {
                MessageBox.Show("Save Map Failed");
            }
        }
        
         protected override bool ProcessCmdKey(ref Message msg, Keys keydata) 
        { 
             switch(keydata)
             {
                 case Keys.Control|Keys.O:
                     this.open();
                     return true;
                 case Keys.Control|Keys.S:
                     worldmap.SaveMap(widthMap, heightMap);
                     MessageBox.Show("Save OK");
                     return true;
             }
            return false; 
        }
    }
}
