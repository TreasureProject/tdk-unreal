// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include <Policies/CondensedJsonPrintPolicy.h>

/**
 * 
 */
namespace TDK
{
    typedef TSharedRef< TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR> > > JsonWriter;
    typedef TSharedRef< TJsonReader<TCHAR> > JsonReader;

    template <typename BoxedType>
    class Boxed
    {
    public:
        BoxedType mValue;

        Boxed() : mValue(), mIsSet(false) {}
        Boxed(BoxedType value) : mValue(value), mIsSet(true) {}

        Boxed& operator=(BoxedType value) { mValue = value; mIsSet = true; return *this; }
        operator BoxedType() { return mValue; }
        operator BoxedType() const { return mValue; }

        void setNull() { mIsSet = false; }
        bool notNull() { return mIsSet; }
        bool notNull() const { return mIsSet; }
        bool isNull() { return !mIsSet; }
        bool isNull() const { return !mIsSet; }
    private:
        bool mIsSet;
    };

    struct TDKCPP_API FTDKCppBaseModel
    {
        virtual ~FTDKCppBaseModel() {}
        virtual void WriteJSON(JsonWriter& Json) const = 0;
        virtual bool ReadFromValue(const TSharedPtr<FJsonObject>& obj) = 0;
        virtual bool ReadFromValue(const TSharedPtr<FJsonValue>& value) { return false; };

        FString toJSONString() const;
    };

    struct TDKCPP_API FTDKCppResultCommon : FTDKCppBaseModel
    {

    };

    void WriteMap(JsonWriter& Writer, FString Identifier, FJsonSerializableKeyValueMap Map);
}
