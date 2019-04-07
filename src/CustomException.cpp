#include "CustomException.h"

// Constructors ------------------------------

CustomException::CustomException(QString s): reason(s){}

CustomException::CustomException(): CustomException("Eccezione non specificata"){}

// Methods ----------------------------------

QString CustomException::getReason()const{ return reason; }

