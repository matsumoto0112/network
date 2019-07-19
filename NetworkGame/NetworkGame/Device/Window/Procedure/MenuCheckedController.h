#pragma once
#include <Windows.h>

namespace Window {

/**
* @class MenuCheckedController
* @brief メニューのチェックを切り替えるコントローラ
*/
class MenuCheckedController {
public:
    /**
    * @brief コンストラクタ
    * @param hWnd ウィンドウハンドル
    * @param itemID メニューのアイテムID
    */
    MenuCheckedController(HWND hWnd,UINT itemID);
    /**
    * @brief デストラクタ
    */
    ~MenuCheckedController();
    /**
    * @brief チェックがついているか
    * @return チェックがついていたらtrueを返す
    */
    bool isChecked() const;
    /**
    * @brief チェックのフラグ設定
    */
    void setChecked(bool checked);
    /**
    * @brief チェックの切り替え
    */
    void switchCheckFlag();
private:
    /**
    * @brief チェック状態の更新
    */
    void updateCheck();
private:
    bool mIsChecked; //!< チェックがついているか
    HMENU mHMenu; //!< メニューハンドル
    UINT mItemID; //!< 管理するアイテムID
};

} //Window 