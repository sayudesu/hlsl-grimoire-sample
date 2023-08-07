﻿#include "stdafx.h"
#include "system/system.h"

// step-1 ディレクションライト用の構造体を定義する
struct DirectionLight
{
    Vector3 lightDirection;

    float pad;

    Vector3 lightColor;
};

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    // ゲームの初期化
    InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

    //////////////////////////////////////
    // ここから初期化を行うコードを記述する
    //////////////////////////////////////

    g_camera3D->SetPosition({ 0.0f, 0.0f, 100.0f });
    g_camera3D->SetTarget({ 0.0f, 0.0f, 0.0f });

    // step-2 ディレクションライトのデータを作成する
    DirectionLight directionLig;

    directionLig.lightDirection.x = 1.0f;
    directionLig.lightDirection.y = -1.0f;
    directionLig.lightDirection.z = -1.0f;

    directionLig.lightDirection.Normalize();

    directionLig.lightColor.x = 0.5f;
    directionLig.lightColor.y = 0.5f;
    directionLig.lightColor.z = 0.5f;

    // step-3 球体モデルを初期化する
    ModelInitData modelInitData;

    modelInitData.m_tkmFilePath = "Assets/modelData/teapot.tkm";
    modelInitData.m_fxFilePath = "Assets/shader/sample.fx";

    modelInitData.m_expandConstantBuffer = &directionLig;
    modelInitData.m_expandConstantBufferSize = sizeof(directionLig);

    Model model;
    model.Init(modelInitData);

    //////////////////////////////////////
    // 初期化を行うコードを書くのはここまで！！！
    //////////////////////////////////////
    auto& renderContext = g_graphicsEngine->GetRenderContext();

    // ここからゲームループ
    while (DispatchWindowMessage())
    {
        // レンダリング開始
        g_engine->BeginFrame();
        //////////////////////////////////////
        // ここから絵を描くコードを記述する
        //////////////////////////////////////

        // step-4 モデルをドローする
        model.Draw(renderContext);
        //////////////////////////////////////
        // 絵を描くコードを書くのはここまで！！！
        //////////////////////////////////////
        // レンダリング終了
        g_engine->EndFrame();
    }
    return 0;
}
