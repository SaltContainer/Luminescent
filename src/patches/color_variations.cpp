#include "il2cpp.hpp"

#include "ColorVariation.hpp"
#include "UnityEngine/Color.hpp"

#include "util.hpp"
#include "logger.hpp"

#define NUM_COLOR_SETS 10

struct ColorSet
{
    // Field
    UnityEngine::Color_o skinFace;
    UnityEngine::Color_o skinMouth;
    UnityEngine::Color_o eyes;
    UnityEngine::Color_o eyebrows;
    UnityEngine::Color_o skinBody;
    UnityEngine::Color_o hair;
};

ColorSet COLOR_SETS[NUM_COLOR_SETS];
bool initialized_color_sets = false;

const int32_t SKIN_FACE_ID = 0;
const int32_t SKIN_MOUTH_ID = 1;
const int32_t EYES_ID = 2;
const int32_t EYEBROWS_ID = 3;
const int32_t SKIN_BODY_ID = 4;
const int32_t HAIR_ID = 5;

// TODO: Move this to an external JSON: https://github.com/rafagafe/tiny-json
ColorSet* getColorSets()
{
    if (!initialized_color_sets)
    {
        COLOR_SETS[0] = (ColorSet) { // White skin Player (DPPt colors)
            .skinFace =     { { 0.9490196, 0.76862746, 0.6627451, 1 } },    // White skin
            .skinMouth =    { { 0.9490196, 0.76862746, 0.6627451, 1 } },    // White skin
            .eyes =         { { 0.72156864, 0.79607844, 0.9019608, 1 } },   // Baby blue
            .eyebrows =     { { 0.23921569, 0.27450982, 0.36862746, 1 } },  // Navy blue
            .skinBody =     { { 0.9490196, 0.76862746, 0.6627451, 1 } },    // White skin
            .hair =         { { 0.23921569, 0.27450982, 0.36862746, 1 } },  // Navy blue
        };
        COLOR_SETS[1] = (ColorSet) { // Darker brown skin Player
            .skinFace =     { { 0.4509804, 0.34117648, 0.24705882, 1 } },   // Darker brown skin
            .skinMouth =    { { 0.4509804, 0.34117648, 0.24705882, 1 } },   // Darker brown skin
            .eyes =         { { 0.5254902, 0.34901962, 0.28235295, 1 } },   // Brown
            .eyebrows =     { { 0.23921569, 0.25490198, 0.29803923, 1 } },  // Black
            .skinBody =     { { 0.4509804, 0.34117648, 0.24705882, 1 } },   // Darker brown skin
            .hair =         { { 0.23921569, 0.25490198, 0.29803923, 1 } },  // Black
        };
        COLOR_SETS[2] = (ColorSet) { // Blonde white skin Player
            .skinFace =     { { 0.9019608, 0.7882353, 0.78039217, 1 } },    // Pale skin
            .skinMouth =    { { 0.9019608, 0.7882353, 0.78039217, 1 } },    // Pale skin
            .eyes =         { { 0.67058825, 0.8901961, 1, 1 } },            // Bright blue
            .eyebrows =     { { 0.8392157, 0.7607843, 0.5294118, 1 } },     // Blonde
            .skinBody =     { { 0.9019608, 0.7882353, 0.78039217, 1 } },    // Pale skin
            .hair =         { { 0.8392157, 0.7607843, 0.5294118, 1 } },     // Blonde
        };
        COLOR_SETS[3] = (ColorSet) { // Light brown skin Player
            .skinFace =     { { 0.69803923, 0.5647059, 0.49019608, 1 } },   // Light brown skin
            .skinMouth =    { { 0.69803923, 0.5647059, 0.49019608, 1 } },   // Light brown skin
            .eyes =         { { 0.8039216, 0.45490196, 0.53333336, 1 } },   // Pink
            .eyebrows =     { { 0.25490198, 0.2, 0.2, 1 } },                // Dark brown
            .skinBody =     { { 0.69803923, 0.5647059, 0.49019608, 1 } },   // Light brown skin
            .hair =         { { 0.25490198, 0.2, 0.2, 1 } },                // Dark brown
        };
        COLOR_SETS[4] = (ColorSet) { // Ace Trainer F
            .skinFace =     { { 0.9490196, 0.8, 0.7058824, 1 } },           // White skin
            .skinMouth =    { { 0.9490196, 0.8, 0.7058824, 1 } },           // White skin
            .eyes =         { { 0.4862745, 0.7294118, 0.40784314, 1 } },    // Green
            .eyebrows =     { { 0.4862745, 0.7294118, 0.40784314, 1 } },    // Green
            .skinBody =     { { 0.9490196, 0.8, 0.7058824, 1 } },           // White skin
            .hair =         { { 0.4862745, 0.7294118, 0.40784314, 1 } },    // Green
        };
        COLOR_SETS[5] = (ColorSet) {
            .skinFace =     { { 0.4509804, 0.34117648, 0.24705882, 1 } },   // Darker brown skin
            .skinMouth =    { { 0.4509804, 0.34117648, 0.24705882, 1 } },   // Darker brown skin
            .eyes =         { { 0.5254902, 0.34901962, 0.28235295, 1 } },   // Brown
            .eyebrows =     { { 0.8392157, 0.7607843, 0.5294118, 1 } },     // Blonde
            .skinBody =     { { 0.4509804, 0.34117648, 0.24705882, 1 } },   // Darker brown skin
            .hair =         { { 0.8392157, 0.7607843, 0.5294118, 1 } },     // Blonde
        };
        COLOR_SETS[6] = (ColorSet) {
            .skinFace =     { { 0.69803923, 0.5647059, 0.49019608, 1 } },   // Light brown skin
            .skinMouth =    { { 0.69803923, 0.5647059, 0.49019608, 1 } },   // Light brown skin
            .eyes =         { { 0.5254902, 0.34901962, 0.28235295, 1 } },   // Brown
            .eyebrows =     { { 0.8392157, 0.7607843, 0.5294118, 1 } },     // Blonde
            .skinBody =     { { 0.69803923, 0.5647059, 0.49019608, 1 } },   // Light brown skin
            .hair =         { { 0.8392157, 0.7607843, 0.5294118, 1 } },     // Blonde
        };
        COLOR_SETS[7] = (ColorSet) {
            .skinFace =     { { 0.9019608, 0.7882353, 0.78039217, 1 } },    // Pale skin
            .skinMouth =    { { 0.9019608, 0.7882353, 0.78039217, 1 } },    // Pale skin
            .eyes =         { { 0.67058825, 0.8901961, 1, 1 } },            // Bright blue
            .eyebrows =     { { 0.8, 0.513725, 0.294118, 1 } },             // Orange
            .skinBody =     { { 0.9019608, 0.7882353, 0.78039217, 1 } },    // Pale skin
            .hair =         { { 0.8, 0.513725, 0.294118, 1 } },             // Orange
        };
        COLOR_SETS[8] = (ColorSet) {
            .skinFace =     { { 0.9490196, 0.76862746, 0.6627451, 1 } },    // White skin
            .skinMouth =    { { 0.9490196, 0.76862746, 0.6627451, 1 } },    // White skin
            .eyes =         { { 0.72156864, 0.79607844, 0.9019608, 1 } },   // Baby blue
            .eyebrows =     { { 0.447059, 0.337255, 0.247059, 1 } },        // Brown
            .skinBody =     { { 0.9490196, 0.76862746, 0.6627451, 1 } },    // White skin
            .hair =         { { 0.447059, 0.337255, 0.247059, 1 } },        // Brown
        };
        COLOR_SETS[9] = (ColorSet) {
            .skinFace =     { { 0.9490196, 0.76862746, 0.6627451, 1 } },    // White skin
            .skinMouth =    { { 0.9490196, 0.76862746, 0.6627451, 1 } },    // White skin
            .eyes =         { { 0.447059, 0.337255, 0.247059, 1 } },        // Brown
            .eyebrows =     { { 0.447059, 0.337255, 0.247059, 1 } },        // Brown
            .skinBody =     { { 0.9490196, 0.76862746, 0.6627451, 1 } },    // White skin
            .hair =         { { 0.447059, 0.337255, 0.247059, 1 } },        // Brown
        };
        initialized_color_sets = true;
    }
    return COLOR_SETS;
}

System::Array<ColorVariation_Property_o> * GetEditedProperty00(ColorVariation_o *variation, int32_t index)
{
    system_load_typeinfo((void *)0x2c09);

    System::Array<ColorVariation_Property_o> *properties = variation->fields.Property00;

    if (properties->max_length > 0)
    {
        System::Array<ColorVariation_Property_MaskColor_o> *colors = properties->m_Items[0].fields.colors;

        if (NUM_COLOR_SETS > index)
        {
            ColorSet set = getColorSets()[index];

            if (colors->max_length > SKIN_FACE_ID) colors->m_Items[SKIN_FACE_ID].fields.color.fields = set.skinFace.fields;
            if (colors->max_length > SKIN_MOUTH_ID) colors->m_Items[SKIN_MOUTH_ID].fields.color.fields = set.skinMouth.fields;
            if (colors->max_length > EYES_ID) colors->m_Items[EYES_ID].fields.color.fields = set.eyes.fields;
            if (colors->max_length > EYEBROWS_ID) colors->m_Items[EYEBROWS_ID].fields.color.fields = set.eyebrows.fields;
            if (colors->max_length > SKIN_BODY_ID) colors->m_Items[SKIN_BODY_ID].fields.color.fields = set.skinBody.fields;
            if (colors->max_length > HAIR_ID) colors->m_Items[HAIR_ID].fields.color.fields = set.hair.fields;
        }
    }

    return properties;
}

void ColorVariation_LateUpdate(ColorVariation_o *__this, MethodInfo *method)
{
    system_load_typeinfo((void *)0x2c09);
    System::Array<ColorVariation_Property_o> *properties = GetEditedProperty00(__this, __this->fields.ColorIndex);

    if (__this->fields.propertyBlock != nullptr && properties->max_length > 0)
    {
        properties->m_Items[0].Update(__this->fields.propertyBlock, nullptr);
    }
}
