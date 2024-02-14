#include "Input.h"
#include "WinApp.h"
#include"DirectXCommon.h"

#include"Sprite.h"
#include"SpriteCommon.h"

#include"ImGuiManager.h"
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Input* input_ = nullptr;
    WinApp* winApp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;
//WindowsAPI初期化処理
    winApp_ = new WinApp();
    winApp_->Initialize();


//DirectX初期化処理
    dxCommon_ = new DirectXCommon();
    dxCommon_->Initialize(winApp_);

    // ポインタ置き場
    input_ = new Input();
    input_->Initialize(winApp_);
    ImGuiManager* imgui = ImGuiManager::Create();
    ImGuiManager::Initialize(winApp_->GetHwnd(), dxCommon_);
    //スプライトコモン
    SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon_);

    //スプライト
    Sprite* sprite = new Sprite();
    sprite->Initialize(dxCommon_,spriteCommon);
    // ゲームループ
    while (true) {
        if (winApp_->Update() == true)
        {
            break;
      }
        ImGuiManager::NewFrame();
        imgui->ShowDemo();
        input_ -> Update();
        sprite->Update();
        //更新前処理
        ImGuiManager::CreateCommand();
        dxCommon_->PreDraw();
        
        sprite->Draw();
        // ４．描画コマンドここまで
        ImGuiManager::CommandsExcute(dxCommon_->GetCommandList());
        dxCommon_->PostDraw();
       
      

    }
    delete sprite;
    delete spriteCommon;
    delete imgui;
    delete input_;
    delete dxCommon_;
    winApp_->Finalize();
    delete winApp_;
    

    return 0;
}
