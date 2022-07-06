using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;
using System.IO;


namespace IconEditor
{
    public partial class MainWindow : Window
    {

        //  Undo,Redo用の変数定義
        Rectangle[,] Rectangles = new Rectangle[32, 32];
        Stack<Color[,]> UndoStack = new Stack<Color[,]>();
        Stack<Color[,]> RedoStack = new Stack<Color[,]>();

        Rectangle[,] Copy = new Rectangle[32, 32];

        public static RoutedCommand UndoCommand { get; }
        = new RoutedCommand(nameof(UndoCommand), typeof(MainWindow));

        public static RoutedCommand RedoCommand { get; }
        = new RoutedCommand(nameof(RedoCommand), typeof(MainWindow));

        public static RoutedCommand SaveAsCommand { get; }
        = new RoutedCommand(nameof(SaveAsCommand), typeof(MainWindow));

        public static RoutedCommand CopyCommand { get; }
        = new RoutedCommand(nameof(CopyCommand), typeof(MainWindow));

        public static RoutedCommand PasteCommand { get; }
        = new RoutedCommand(nameof(PasteCommand), typeof(MainWindow));

        public MainWindow()
        {
            InitializeComponent();
        }

        //Create grid-like picture on h:32 * w:32
        private void MainCanvas2_Initialized(object sender, EventArgs e)
        {
            Canvas canvas = (Canvas)sender;

            for(int y = 0; y < 32; y++)
            {
                for(int x = 0; x < 32; x++)
                {
                    Rectangle rect;
                    rect = new Rectangle();
                    rect.Fill = new SolidColorBrush(Colors.White);
                    rect.Width = 19;
                    rect.Height = 19;
                    rect.MouseDown += Rectangle_MouseDown;
                    rect.MouseMove += Rectangle_MouseMove;


                    Canvas.SetLeft(rect, x * 20);
                    Canvas.SetTop(rect, y * 20);

                    canvas.Children.Add(rect);

                    //  RectAngles初期化
                    Rectangles[y, x] = rect;
                   
                }
            }

            
        }

        private void Rectangle_MouseDown(object sender, MouseButtonEventArgs e)
        {
            //  UndoStackに色をプッシュ
            {
                Color[,] color = new Color[32, 32];

                for(int y = 0; y < 32; y++)
                {
                    for(int x = 0; x < 32; x++)
                    {
                        SolidColorBrush brush = (SolidColorBrush)Rectangles[y, x].Fill;
                        color[y, x] = Color.FromArgb(brush.Color.A, brush.Color.R, brush.Color.G, brush.Color.B);
                    }
                }

                RedoStack.Clear();
                UndoStack.Push(color);


            }

            //  色を塗る処理
            Rectangle rect = (Rectangle)sender;
            SolidColorBrush puletteBrush = (SolidColorBrush)ColorPalette.Fill;
            rect.Fill = new SolidColorBrush(puletteBrush.Color);
        }

        private void Rectangle_MouseMove(object sender, MouseEventArgs  e)
        {
            Rectangle rect = (Rectangle)sender;

            String text;

            int x = (int)Canvas.GetLeft(rect) / 20;
            int y = (int)Canvas.GetTop(rect) / 20;

            text = "列:" + x.ToString() +"、"+ "行" + y.ToString();

            StatusBarLabel.Content = text;

            if(e.LeftButton == MouseButtonState.Pressed)
            {
                //rect.Fill = new SolidColorBrush(Color.FromArgb(255, 0, 0, 255));
                SolidColorBrush puletteBrush = (SolidColorBrush)ColorPalette.Fill;
                rect.Fill = new SolidColorBrush(puletteBrush.Color);
            }
            
        }

        
        private void MenuItem_Finalize_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void MenuItem_New_Click(object sender, RoutedEventArgs e)
        {
            
        }

        private void MenuItem_Version_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("☆スター・バースト・アイコン・エディター☆\nVersion 0.0.1",
                "☆スター・バースト・アイコン・エディター☆　のバージョン情報",
                MessageBoxButton.OK,
                MessageBoxImage.Information,
                MessageBoxResult.Yes);
        }

        private void MenuItem_ZoomOut_Click(object sender, RoutedEventArgs e)
        {
            int index = Slider_Zoom.Ticks.IndexOf(Slider_Zoom.Value);
            index--;

            if (0 > index)
                return;

            Slider_Zoom.Value = Slider_Zoom.Ticks[index];

            //ステータスバーの拡大率を変更
            StatusBarLabel_Scale.Content = "拡大率：" + Slider_Zoom.Value.ToString() + "%";
        }

        private void MenuItem_ZoomIn_Click(object sender, RoutedEventArgs e)
        {
            int index = Slider_Zoom.Ticks.IndexOf(Slider_Zoom.Value);
            index++;

            if (Slider_Zoom.Ticks.Count <= index)
                return;

            Slider_Zoom.Value = Slider_Zoom.Ticks[index];

            //ステータスバーの拡大率を変更
            StatusBarLabel_Scale.Content = "拡大率：" + Slider_Zoom.Value.ToString() + "%";
        }

        private void Slider_Zoom_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (MainCanvas2 == null) return;

            //Matrixを使うと拡縮とか使える
            Matrix matrix = new Matrix();

            //*0.01にしているのはパーセントを0.1とかに直している
            matrix.Scale(Slider_Zoom.Value * 0.01, Slider_Zoom.Value * 0.01);
            matrixTransform.Matrix = matrix;

            //%の表示を変える
            ZoomLavel.Content = Slider_Zoom.Value + "%";

            //ステータスバーの拡大率を変更
            StatusBarLabel_Scale.Content = "拡大率：" + Slider_Zoom.Value.ToString()+"%";


            //メインキャンバスの大きさを変える
            MainCanvas2.Width = 640 * Slider_Zoom.Value * 0.01;
            MainCanvas2.Height = 640 * Slider_Zoom.Value * 0.01;
        }




        //  CTRL+マウスホイールで拡縮
        private void MainCanvas2_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            if ((Keyboard.GetKeyStates(Key.LeftCtrl) & KeyStates.Down) == KeyStates.Down ||
                (Keyboard.GetKeyStates(Key.RightCtrl) & KeyStates.Down) == KeyStates.Down)
            {
                if (e.Delta > 0)
                {
                    MenuItem_ZoomIn_Click(sender, e);
                }
                else
                {
                    MenuItem_ZoomOut_Click(sender, e);
                }
            }
        }

        private void ColorPalette_MouseDown(object sender, MouseButtonEventArgs e)
        {
            //  カラーダイアログを呼び出す
            System.Windows.Forms.ColorDialog cd = new System.Windows.Forms.ColorDialog();

            cd.FullOpen = true;

            //  カラーダイアログの色を設定
            SolidColorBrush paletteBrush = (SolidColorBrush)ColorPalette.Fill;
            cd.Color = System.Drawing.Color.FromArgb(paletteBrush.Color.A,
                paletteBrush.Color.R, paletteBrush.Color.G, paletteBrush.Color.B);

            //  ウィンドウが表示され、OKが押されたら
            if(cd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                //  RectAngleを塗る色として設定
                Color color = Color.FromArgb(cd.Color.A, cd.Color.R, cd.Color.G, cd.Color.B);
                ColorPalette.Fill = new SolidColorBrush(color);
            }

        }
        private void MenuItem_Undo_Click_Can(object sender, CanExecuteRoutedEventArgs e)
        {
            if (UndoStack.Count == 0)
                e.CanExecute = false;
            else
                e.CanExecute = true;
        }
        private void MenuItem_Undo_Click(object sender, RoutedEventArgs e)
        {
            if (UndoStack.Count == 0) return;

            {
                {
                    Color[,] color = new Color[32, 32];

                    for (int y = 0; y < 32; y++)
                    {
                        for (int x = 0; x < 32; x++)
                        {
                            SolidColorBrush brush = (SolidColorBrush)Rectangles[y, x].Fill;
                            color[y, x] = Color.FromArgb(brush.Color.A, brush.Color.R, brush.Color.G, brush.Color.B);
                        }
                    }

                    RedoStack.Push(color);
                }
            }

            {
                Color[,] color = UndoStack.Pop();                

                for (int y = 0; y < 32; y++)
                {
                    for (int x = 0; x < 32; x++)
                    {
                        Rectangles[y, x].Fill = new SolidColorBrush(color[y, x]);
                    }
                }                
            }           
        }

        private void MenuItem_Redo_Click_Can(object sender, CanExecuteRoutedEventArgs e)
        {
            if (RedoStack.Count == 0)
                e.CanExecute = false;
            else
                e.CanExecute = true;
        }
        private void MenuItem_Redo_Click(object sender, RoutedEventArgs e)
        {
            if (RedoStack.Count == 0) return;

            {
                {
                    Color[,] color = new Color[32, 32];

                    for (int y = 0; y < 32; y++)
                    {
                        for (int x = 0; x < 32; x++)
                        {
                            SolidColorBrush brush = (SolidColorBrush)Rectangles[y, x].Fill;
                            color[y, x] = Color.FromArgb(brush.Color.A, brush.Color.R, brush.Color.G, brush.Color.B);
                        }
                    }

                    UndoStack.Push(color);
                }
            }

            {
                Color[,] color = RedoStack.Pop();
                

                for (int y = 0; y < 32; y++)
                {
                    for (int x = 0; x < 32; x++)
                    {
                        Rectangles[y, x].Fill = new SolidColorBrush(color[y, x]);
                    }
                }

            }

        }

        private void Button_Undo_Click(object sender, RoutedEventArgs e)
        {
            MenuItem_Undo_Click(sender,e);
        }

        private void Button_Redo_Click(object sender, RoutedEventArgs e)
        {
            MenuItem_Redo_Click(sender, e);
        }

        private void Button_Undo_KeyDown(object sender, KeyEventArgs e)
        {
            
        }

        private void MenuItem_SaveAs_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "PNG(*.png)| *.png";

            //  値無しを認める
            bool? result = dlg.ShowDialog();

            //  保存が押されていない　＝　キャンセルが押された
            if (result != true) return;

            //  ビットマップ用意
            WriteableBitmap bitmap = new WriteableBitmap(32, 32, 300, 300, PixelFormats.Bgra32, null);

            //  バイト型の配列を作る  32*32*4 -> 縦×横×ピクセル数
            byte[] pixels = new byte[32 * 32 * 4];

            //  縦
            for(int y = 0; y < 32; y++)
            {
                //  横
                for(int x = 0; x < 32; x++)
                {
                    SolidColorBrush brush = (SolidColorBrush)Rectangles[y, x].Fill;

                    pixels[(y * 32 + x) * 4 + 0] = brush.Color.B;
                    pixels[(y * 32 + x) * 4 + 1] = brush.Color.G;
                    pixels[(y * 32 + x) * 4 + 2] = brush.Color.R;
                    pixels[(y * 32 + x) * 4 + 3] = brush.Color.A;
                }
            }

            bitmap.WritePixels(new Int32Rect(0, 0, 32, 32), pixels, 32 * 4, 0);

            using (FileStream stream = new FileStream(dlg.FileName, FileMode.Create, FileAccess.Write))
            {
                PngBitmapEncoder encoder = new PngBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(bitmap));
                encoder.Save(stream);
            }
        }

        private void MenuItem_Open_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "PNG(*.png)| *.png";

            //  値無しを認める
            bool? result = dlg.ShowDialog();

            //  保存が押されていない　＝　キャンセルが押された
            if (result != true) return;

            byte[] pixels = new byte[32 * 32 * 4];

            using (FileStream stream = new FileStream(dlg.FileName,FileMode.Open,FileAccess.Read))
            {
                PngBitmapDecoder decoder = new PngBitmapDecoder(stream, BitmapCreateOptions.PreservePixelFormat,
                    BitmapCacheOption.Default);

                BitmapSource bitmap = decoder.Frames[0];
                bitmap.CopyPixels(pixels, 32 * 4, 0);
            }

            Color[,] color = new Color[32, 32];

            for (int y = 0; y < 32; y++)
            {
                //  横
                for (int x = 0; x < 32; x++)
                {
                    color[y, x].B = pixels[(y * 32 + x) * 4 + 0];
                    color[y, x].G = pixels[(y * 32 + x) * 4 + 1];
                    color[y, x].R = pixels[(y * 32 + x) * 4 + 2];
                    color[y, x].A = pixels[(y * 32 + x) * 4 + 3];

                    Rectangles[y, x].Fill = new SolidColorBrush(color[y, x]);
                }
            }

            

        }

        private void MenuItem_NewIn_Empty_Click(object sender, RoutedEventArgs e)
        {
            Color[,] color = new Color[32, 32];

            for (int y = 0; y < 32; y++)
            {
                for (int x = 0; x < 32; x++)
                {
                    Rectangles[y,x].Fill = new SolidColorBrush(Colors.White);
                }
            }
           
        }

        private void MenuItem_Copy_Click(object sender, RoutedEventArgs e)
        {
            byte[] pixels = new byte[32 * 32 * 4];

            //  ここにpixelsに色を保存するコード
            //  縦
            for (int y = 0; y < 32; y++)
            {
                //  横
                for (int x = 0; x < 32; x++)
                {
                    SolidColorBrush brush = (SolidColorBrush)Rectangles[y, x].Fill;

                    pixels[(y * 32 + x) * 4 + 0] = brush.Color.B;
                    pixels[(y * 32 + x) * 4 + 1] = brush.Color.G;
                    pixels[(y * 32 + x) * 4 + 2] = brush.Color.R;
                    pixels[(y * 32 + x) * 4 + 3] = brush.Color.A;
                }
            }           

            WriteableBitmap bitmap = new WriteableBitmap(32, 32, 300, 300, PixelFormats.Bgra32, null);
            bitmap.WritePixels(new Int32Rect(0, 0, 32, 32), pixels, 32 * 4, 0, 0);

            Clipboard.SetImage(bitmap);
            
        }

        private void MenuItem_Paste_Click(object sender, RoutedEventArgs e)
        {                                   
            BitmapSource source = Clipboard.GetImage();
            if (source == null)
                return;

            byte[] pixels = new byte[source.PixelWidth * source.PixelHeight * 4];


            source.CopyPixels( pixels, source.PixelWidth * 4, 0);

            Color[,] color = new Color[32, 32];

            int width = Math.Min(32, source.PixelWidth);
            int height = Math.Min(32, source.PixelHeight);

            //  縦
            for (int y = 0; y < height; y++)
            {
                //  横
                for (int x = 0; x < width; x++)
                {                    
                    color[y, x].B = pixels[(y * source.PixelWidth + x) * 4 + 0];
                    color[y, x].G = pixels[(y * source.PixelWidth + x) * 4 + 1];
                    color[y, x].R = pixels[(y * source.PixelWidth + x) * 4 + 2];
                    color[y, x].A = 255;

                    Rectangles[y, x].Fill = new SolidColorBrush(color[y, x]);
                }
            }

            UndoStack.Push(color);
        }

       

        private void MenuItem_Copy_Click_Can(object sender, CanExecuteRoutedEventArgs e)
        {

        }

        private void MenuItem_Paste_Click_Can(object sender, CanExecuteRoutedEventArgs e)
        {

        }
    }
}
