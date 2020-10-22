#include <sstream>
#include <string>
#include <map>

#include "beatsaber-hook/shared/utils/utils.h"
#include "CustomTypes/Components/Backgroundable.hpp"
#include "ArrayUtil.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "HMUI/ImageView.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/HideFlags.hpp"

DEFINE_CLASS(QuestUI::Backgroundable);

std::map<std::string, std::string> backgrounds =  {
    {
		"round-rect-panel",
		"RoundRect10"
	},
	{
	    "panel-top",
	    "RoundRect10"
	},
	{
		"panel-fade-gradient",
		"RoundRect10Thin"
	},
	{
		"panel-top-gradient",
		"RoundRect10"
	}
};

std::map<std::string, std::string> objectNames =  {
    {
		"round-rect-panel",
		"KeyboardWrapper"
	},
	{
		"panel-top",
		"BG"
	},
	{
		"panel-fade-gradient",
		"Background"
	},
	{
		"panel-top-gradient",
		"BG"
	}
};

std::map<std::string, std::string> objectParentNames =  {
    {
		"round-rect-panel",
		"Wrapper"
	},
	{
		"panel-top",
		"PracticeButton"
	},
	{
		"panel-fade-gradient",
		"LevelListTableCell"
	},
	{
		"panel-top-gradient",
		"ActionButton"
	}
};

void QuestUI::Backgroundable::ApplyBackground(Il2CppString* name) {
    if(background)
        return;
    std::string stringName = to_utf8(csstrtostr(name));
    HMUI::ImageView* search = ArrayUtil::Last(UnityEngine::Resources::FindObjectsOfTypeAll<HMUI::ImageView*>(), [&stringName](HMUI::ImageView* x){ 
        UnityEngine::Sprite* sprite = x->get_sprite();
        if(sprite && to_utf8(csstrtostr(sprite->get_name())) != backgrounds[stringName])
            return false;
		if(sprite && to_utf8(csstrtostr(x->get_transform()->get_parent()->get_name())) != objectParentNames[stringName])
            return false;
        return to_utf8(csstrtostr(x->get_name())) == objectNames[stringName]; 
    });
    if(!search)
        return;
    background = get_gameObject()->AddComponent<HMUI::ImageView*>();
    //Copy Image: some methods are probably not needed
    background->set_alphaHitTestMinimumThreshold(search->get_alphaHitTestMinimumThreshold());
    background->set_color(search->get_color());
    background->set_eventAlphaThreshold(search->get_eventAlphaThreshold());
    background->set_fillAmount(search->get_fillAmount());
    background->set_fillCenter(search->get_fillCenter());
    background->set_fillClockwise(search->get_fillClockwise());
    background->set_fillMethod(search->get_fillMethod());
    background->set_fillOrigin(search->get_fillOrigin());
    background->set_hideFlags(search->get_hideFlags());
    background->set_maskable(search->get_maskable());
    background->set_material(search->get_material());
    background->set_name(search->get_name());
    background->set_onCullStateChanged(search->get_onCullStateChanged());
    background->set_overrideSprite(search->get_overrideSprite());
    background->set_pixelsPerUnitMultiplier(search->get_pixelsPerUnitMultiplier());
    background->set_preserveAspect(search->get_preserveAspect());
    background->set_raycastTarget(search->get_raycastTarget());
    background->set_sprite(search->get_sprite());
    background->set_tag(search->get_tag());
    background->set_type(search->get_type());
    background->set_useGUILayout(search->get_useGUILayout());
    background->set_useLegacyMeshGeneration(search->get_useLegacyMeshGeneration());
    background->set_useSpriteMesh(search->get_useSpriteMesh());

    background->set_enabled(true);
}