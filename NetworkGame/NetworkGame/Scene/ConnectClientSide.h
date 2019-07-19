#pragma once

#include "Scene/IScene.h"
#include <Windows.h>
#include <memory>
#include <string>

namespace Network {
class GameClientThread;
} //Network 

namespace Graphics {
class TextureString;
} //Graphics 

namespace Scene {

/**
* @class ConnectClientSide
* @brief クライアント側のサーバー接続シーン
*/
class ConnectClientSide :public IScene {
public:
    /**
    * @brief コンストラクタ
    */
    ConnectClientSide();
    /**
    * @brief デストラクタ
    */
    ~ConnectClientSide();
    /**
    * @brief 更新
    * @param delta 前フレームからの差分時間
    */
    virtual void update(float delta) override;
    /**
    * @brief シーンが終了しているか
    */
    virtual bool isEndScene() const override;
    /**
    * @brief 描画
    */
    virtual void draw() override;
    /**
    * @brief 終了時処理
    * @return 次のシーン
    */
    virtual std::unique_ptr<IScene> end() override;
private:
    /**
    * @brief 接続ボタンが押されたときのイベント
    * @param address サーバーアドレス
    * @param port ポート番号
    */
    void pushConnectButton(const std::string& address,int port);
private:
    bool mIsSceneEnd; //!< シーンが終了しているか 
    bool mIsSelectConnect; //!< 接続が押されたか
    HWND mDlg; //!< ダイアログハンドル
    std::unique_ptr<Graphics::TextureString> mStr; //!< 表示するUI文字列
    std::unique_ptr<Network::GameClientThread> mClient; //!< クライアントスレッド
};

} //Scene 