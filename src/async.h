/* Copyright (c) 2012-2015 LevelDOWN contributors
 * See list at <https://github.com/level/leveldown#contributing>
 * MIT License <https://github.com/level/leveldown/blob/master/LICENSE.md>
 */

#if defined(JS_ENGINE_V8) or defined(JS_ENGINE_MOZJS) or \
    defined(JS_ENGINE_CHAKRA)
#ifndef LD_ASYNC_H
#define LD_ASYNC_H

#include <node.h>
#include "nan.h"
#include "database.h"

namespace leveldown {

class Database;

/* abstract */ class AsyncWorker : public NanAsyncWorker {
 public:
  node::commons* com_;

  AsyncWorker(leveldown::Database* database, NanCallback* callback)
      : NanAsyncWorker(callback), database(database) {
    JS_ENTER_SCOPE_COM();
    JS_DEFINE_STATE_MARKER(com);
    com_ = com;
    JS_LOCAL_OBJECT obj = JS_NEW_EMPTY_OBJECT();
    JS_NEW_PERSISTENT_OBJECT(persistentHandle, obj);
  }

 protected:
  void SetStatus(leveldb::Status status) {
    this->status = status;
    if (!status.ok()) SetErrorMessage(status.ToString().c_str());
  }
  Database* database;

 private:
  leveldb::Status status;
};

}  // namespace leveldown

#endif
#endif
