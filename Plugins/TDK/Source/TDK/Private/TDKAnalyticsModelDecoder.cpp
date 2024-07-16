// Fill out your copyright notice in the Description page of Project Settings.


#include "TDKAnalyticsModelDecoder.h"

#include "TDKJsonObject.h"

FSendEventResult UTDKAnalyticsModelDecoder::DecodeSendEventResponse(UTDKJsonObject* Response)
{
	FSendEventResult Result;

    UTDKJsonObject* SendMessageResponse = !(Response->HasField("SendMessageResponse")) ? nullptr : Response->GetObjectField("SendMessageResponse");

    UTDKJsonObject* ResponseMetadata = !(SendMessageResponse->HasField("ResponseMetadata")) ? nullptr : SendMessageResponse->GetObjectField("ResponseMetadata");
    UTDKJsonObject* SendMessageResult = !(SendMessageResponse->HasField("SendMessageResult")) ? nullptr : SendMessageResponse->GetObjectField("SendMessageResult");

    Result.RequestId = !(ResponseMetadata->HasField("RequestId")) ? TEXT("") : ResponseMetadata->GetStringField("RequestId");
    Result.MD5OfMessageAttributes = !(SendMessageResult->HasField("MD5OfMessageAttributes")) ? nullptr : SendMessageResult->GetObjectField("MD5OfMessageAttributes");
    Result.MD5OfMessageBody = !(SendMessageResult->HasField("MD5OfMessageBody")) ? TEXT("") : SendMessageResult->GetStringField("MD5OfMessageBody");
    Result.MD5OfMessageSystemAttributes = !(SendMessageResult->HasField("MD5OfMessageSystemAttributes")) ? nullptr : SendMessageResult->GetObjectField("MD5OfMessageSystemAttributes");
    Result.MessageId = !(SendMessageResult->HasField("MessageId")) ? TEXT("") : SendMessageResult->GetStringField("MessageId");
    Result.SequenceNumber = !(SendMessageResult->HasField("SequenceNumber")) ? TEXT("") : SendMessageResult->GetStringField("SequenceNumber");

	return Result;
}
