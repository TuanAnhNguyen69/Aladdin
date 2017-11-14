using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace MapEditor
{
    struct QuadTree{

    }
    class Quadtree
    {
        private int nodeID;
        private int level;        
        private	Rectangle region;
        private List<Object> objList;
        public Quadtree _nodeTL; // Node con left top
        public Quadtree _nodeTR; // Node con right top
        public Quadtree _nodeBL; // Node con left bottom
        public Quadtree _nodeBR; // Node con right bottom

        public Quadtree()
        {

        }

        public Quadtree(int id, int pLevel, Rectangle _region)
        {
            this.nodeID = id;            
            this.level = pLevel;
            this.region = _region;
            this.objList = new List<Object>();
            this._nodeTL = null;
            this._nodeTR = null;
            this._nodeBL = null;
            this._nodeBR = null;
        }
        //Kiểm tra xem obj truyền vào có nằm trong phạm vi node không
        private bool IsContain(Object obj)
        {
            Rectangle bound = obj.Rec;

	        return !(bound.X + bound.Width < region.X ||
		        bound.Y + bound.Height < region.Y||
		        bound.X > region.X + region.Width ||
		        bound.Y> region.Y + region.Height);
        }
        //Chia node
		private	void Split()
        {
            int subWidth = (int)(region.Width / 2);
            int subHeight = (int)(region.Height / 2);
            int x = (int)region.X;
            int y = (int)region.Y;

            _nodeTL = new Quadtree(this.nodeID * 8 + 1, level + 1, new Rectangle(x, y, subWidth, subHeight));
            _nodeTR = new Quadtree(this.nodeID * 8 + 2, level + 1, new Rectangle(x + subWidth, y, subWidth, subHeight));
            _nodeBL = new Quadtree(this.nodeID * 8 + 3, level + 1, new Rectangle(x, y + subHeight, subWidth, subHeight));
            _nodeBR = new Quadtree(this.nodeID * 8 + 4, level + 1, new Rectangle(x + subWidth, y + subHeight, subWidth, subHeight));
        }

        //Thêm Obj vào quad tree
		public void Insert(Object obj)
        {
            //Nếu node hiện tại không phải là node lá
            if (this._nodeTL != null)
            {
                if (this._nodeTL.IsContain(obj))
                    this._nodeTL.Insert(obj);
                if (this._nodeTR.IsContain(obj))
                    this._nodeTR.Insert(obj);
                if (this._nodeBL.IsContain(obj))
                    this._nodeBL.Insert(obj);
                if (this._nodeBR.IsContain(obj))
                    this._nodeBR.Insert(obj);
            }

            //Chèn obj vào node hiện tại
            if (this.IsContain(obj))
                this.objList.Add(obj);

            //Tiếp tục chia node nếu thỏa điều kiện
            if (objList.Count > 0 && region.Width > 640)
            {
                Split();
                foreach(Object o in this.objList)
                {
                    if (this._nodeTL.IsContain(o))
                        this._nodeTL.Insert(o);
                    if (this._nodeTR.IsContain(o))
                        this._nodeTR.Insert(o);
                    if (this._nodeBL.IsContain(o))
                        this._nodeBL.Insert(o);
                    if (this._nodeBR.IsContain(o))
                        this._nodeBR.Insert(o);
                }                
            }
        }

        //Lấy list quad node
        public void GetListObject(List<int[]> listQuadtree)
        {
            if (this._nodeTL != null)
            {
                this.objList.Clear();
                this._nodeTL.GetListObject(listQuadtree);
                this._nodeTR.GetListObject(listQuadtree);
                this._nodeBL.GetListObject(listQuadtree);
                this._nodeBR.GetListObject(listQuadtree);
            }
            //5 phần tử đầu lưu thông tin node
            //từ phần tử thứ 6 trở đi lưu danh sách id obj của node
            int[] a = new int[this.objList.Count + 5];
            a[0] = this.nodeID;
            a[1] = this.region.X;
            a[2] = this.region.Y;
            a[3] = this.region.Width;
            a[4] = this.region.Height;
            int i = 5;  
            if(this.objList != null)
            {
                foreach (Object obj in this.objList)
                {
                    a[i] = obj.Id;
                    i++;
                }
            }            
            listQuadtree.Add(a);
        }
    }
}
