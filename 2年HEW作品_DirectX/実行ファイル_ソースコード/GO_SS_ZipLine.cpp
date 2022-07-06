//#include "GO_SS_ZipLine.h"
//
//void GO_SS_ZipLine::Initialize(void)
//{
//	poleTex = LoadTexture("data/TEXTURE/Pole.png");
//    wireTex = LoadTexture("data/TEXTURE/Wire.png");
//
//    for (int i = 0; i < ZIPLINE_MAX; i++)
//    {
//        ziplineInfo[i].pos = D3DXVECTOR2(0.0f, 0.0f);
//        ziplineInfo[i].size = D3DXVECTOR2(WALL_WIDTH / 5, WALL_HEIGHT * POLE_WALL_HEIGHT);
//        ziplineInfo[i].use = false;
//        ziplineInfo[i].poleB_pos = D3DXVECTOR2(0.0f, 0.0f);
//        ziplineInfo[i].angle = 0.0f;
//    }
//}
//
//void GO_SS_ZipLine::Finalize(void)
//{
//}
//
//void GO_SS_ZipLine::Update(void)
//{
//
//}
//
//void GO_SS_ZipLine::Draw(void)
//{
//    for (int i = 0; i < ZIPLINE_MAX; i++)
//    {
//        if (ziplineInfo[i].use)
//        { 
//            //ƒƒCƒ„[•`‰æ
//            DrawSpriteColorRotate(wireTex, ziplineInfo[i].pos.x, ziplineInfo[i].pos.y,
//                ziplineInfo[i].poleBdistance * (WALL_WIDTH * 2) + ziplineInfo[i].size.x*2, 20,
//                0.1f, 0.1f, 0.8f, 0.8f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), ziplineInfo[i].angle);
//
//            //’Œ•`‰æ
//            DrawSpriteLeftTop(poleTex, ziplineInfo[i].pos.x , ziplineInfo[i].pos.y, 
//                ziplineInfo[i].size.x, ziplineInfo[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f);
//            DrawSpriteLeftTop(poleTex, ziplineInfo[i].poleB_pos.x, ziplineInfo[i].poleB_pos.y,
//                ziplineInfo[i].size.x, ziplineInfo[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f);
//        }
//    }
//}
//
//void GO_SS_ZipLine::SetZipLine(D3DXVECTOR2 pos)
//{
//    for (int i = 0; i < ZIPLINE_MAX; i++)
//    {
//        if (ziplineInfo[i].use) 
//            continue;
//
//        ziplineInfo[i].pos = pos;
//        ziplineInfo[i].angle = atan2f(ziplineInfo[i].poleB_pos.y - ziplineInfo[i].pos.y,
//            ziplineInfo[i].poleB_pos.x - ziplineInfo[i].pos.x);
//        ziplineInfo[i].use = true;
//        break;
//    }
//}
//
//void GO_SS_ZipLine::AddX(FLOAT x)
//{
//    for (int i = 0; i < ZIPLINE_MAX; i++) {
//        if (!ziplineInfo[i].use)continue;
//        ziplineInfo[i].pos.x += x;
//        ziplineInfo[i].poleB_pos.x += x;
//    }
//}
//
//void GO_SS_ZipLine::LinkZipLineB(D3DXVECTOR2 pos, int poleBdistance)
//{
//    for (int i = 0; i < ZIPLINE_MAX; i++) {
//        if (ziplineInfo[i].use)
//            continue;
//        ziplineInfo[i].poleBdistance = poleBdistance;
//        ziplineInfo[i].poleB_pos = pos;
//        break;
//    }
//}
