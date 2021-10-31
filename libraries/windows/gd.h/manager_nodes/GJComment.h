#ifndef __GJCOMMENT_H__
#define __GJCOMMENT_H__

#include <gd.h>

namespace gd
{
    class GJComment : public cocos2d::CCNode
    {
    protected:
        std::string m_sComment;
        std::string m_sUnk;
        int m_nCommentID;
        int m_nAuthorPlayerID;
        int m_nLikes;
        int m_nLevelID;
        bool m_bIsSpam;
        int m_nAuthorAccountID;
        std::string m_sCommentAge;
        char m_bUnk;
        int m_nPercentage;
        int m_nModBadge;  // 1 for normal, 2 for elder
        cocos2d::ccColor3B m_cColor;
        bool m_bHasLevelID;
        GJUserScore* m_pUserScore;

    public:
        int getModBadge() { return this->m_nModBadge; }
    };
}

#endif
