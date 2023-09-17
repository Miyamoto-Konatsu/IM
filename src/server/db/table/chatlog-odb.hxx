// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef CHATLOG_ODB_HXX
#define CHATLOG_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 20475UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "chatlog.h"

#include <memory>
#include <cstddef>
#include <utility>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/result.hxx>
#include <odb/simple-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb
{
  // ChatLog
  //
  template <>
  struct class_traits< ::ChatLog >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::ChatLog >
  {
    public:
    typedef ::ChatLog object_type;
    typedef ::ChatLog* pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef ::uint64 id_type;

    static const bool auto_id = true;

    static const bool abstract = false;

    static id_type
    id (const object_type&);

    typedef
    no_op_pointer_cache_traits<pointer_type>
    pointer_cache_traits;

    typedef
    no_op_reference_cache_traits<object_type>
    reference_cache_traits;

    static void
    callback (database&, object_type&, callback_event);

    static void
    callback (database&, const object_type&, callback_event);
  };
}

#include <odb/details/buffer.hxx>

#include <odb/mysql/version.hxx>
#include <odb/mysql/forward.hxx>
#include <odb/mysql/binding.hxx>
#include <odb/mysql/mysql-types.hxx>
#include <odb/mysql/query.hxx>

namespace odb
{
  // ChatLog
  //
  template <typename A>
  struct query_columns< ::ChatLog, id_mysql, A >
  {
    // id
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::uint64,
        mysql::id_ulonglong >::query_type,
      mysql::id_ulonglong >
    id_type_;

    static const id_type_ id;

    // fromUserId
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        char[32],
        mysql::id_string >::query_type,
      mysql::id_string >
    fromUserId_type_;

    static const fromUserId_type_ fromUserId;

    // toUserId
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        char[32],
        mysql::id_string >::query_type,
      mysql::id_string >
    toUserId_type_;

    static const toUserId_type_ toUserId;

    // conversaionId
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        char[64],
        mysql::id_string >::query_type,
      mysql::id_string >
    conversaionId_type_;

    static const conversaionId_type_ conversaionId;

    // content
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::std::string,
        mysql::id_string >::query_type,
      mysql::id_string >
    content_type_;

    static const content_type_ content;

    // time
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::int64_t,
        mysql::id_longlong >::query_type,
      mysql::id_longlong >
    time_type_;

    static const time_type_ time;

    // seq
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::int64_t,
        mysql::id_longlong >::query_type,
      mysql::id_longlong >
    seq_type_;

    static const seq_type_ seq;

    // platform
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        int,
        mysql::id_long >::query_type,
      mysql::id_long >
    platform_type_;

    static const platform_type_ platform;

    // msgType
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        int,
        mysql::id_long >::query_type,
      mysql::id_long >
    msgType_type_;

    static const msgType_type_ msgType;

    // groupId
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        char[32],
        mysql::id_string >::query_type,
      mysql::id_string >
    groupId_type_;

    static const groupId_type_ groupId;
  };

  template <typename A>
  const typename query_columns< ::ChatLog, id_mysql, A >::id_type_
  query_columns< ::ChatLog, id_mysql, A >::
  id (A::table_name, "`id`", 0);

  template <typename A>
  const typename query_columns< ::ChatLog, id_mysql, A >::fromUserId_type_
  query_columns< ::ChatLog, id_mysql, A >::
  fromUserId (A::table_name, "`fromUserId`", 0);

  template <typename A>
  const typename query_columns< ::ChatLog, id_mysql, A >::toUserId_type_
  query_columns< ::ChatLog, id_mysql, A >::
  toUserId (A::table_name, "`toUserId`", 0);

  template <typename A>
  const typename query_columns< ::ChatLog, id_mysql, A >::conversaionId_type_
  query_columns< ::ChatLog, id_mysql, A >::
  conversaionId (A::table_name, "`conversaionId`", 0);

  template <typename A>
  const typename query_columns< ::ChatLog, id_mysql, A >::content_type_
  query_columns< ::ChatLog, id_mysql, A >::
  content (A::table_name, "`content`", 0);

  template <typename A>
  const typename query_columns< ::ChatLog, id_mysql, A >::time_type_
  query_columns< ::ChatLog, id_mysql, A >::
  time (A::table_name, "`time`", 0);

  template <typename A>
  const typename query_columns< ::ChatLog, id_mysql, A >::seq_type_
  query_columns< ::ChatLog, id_mysql, A >::
  seq (A::table_name, "`seq`", 0);

  template <typename A>
  const typename query_columns< ::ChatLog, id_mysql, A >::platform_type_
  query_columns< ::ChatLog, id_mysql, A >::
  platform (A::table_name, "`platform`", 0);

  template <typename A>
  const typename query_columns< ::ChatLog, id_mysql, A >::msgType_type_
  query_columns< ::ChatLog, id_mysql, A >::
  msgType (A::table_name, "`msgType`", 0);

  template <typename A>
  const typename query_columns< ::ChatLog, id_mysql, A >::groupId_type_
  query_columns< ::ChatLog, id_mysql, A >::
  groupId (A::table_name, "`groupId`", 0);

  template <typename A>
  struct pointer_query_columns< ::ChatLog, id_mysql, A >:
    query_columns< ::ChatLog, id_mysql, A >
  {
  };

  template <>
  class access::object_traits_impl< ::ChatLog, id_mysql >:
    public access::object_traits< ::ChatLog >
  {
    public:
    struct id_image_type
    {
      unsigned long long id_value;
      my_bool id_null;

      std::size_t version;
    };

    struct image_type
    {
      // id_
      //
      unsigned long long id_value;
      my_bool id_null;

      // fromUserId_
      //
      details::buffer fromUserId_value;
      unsigned long fromUserId_size;
      my_bool fromUserId_null;

      // toUserId_
      //
      details::buffer toUserId_value;
      unsigned long toUserId_size;
      my_bool toUserId_null;

      // conversaionId_
      //
      details::buffer conversaionId_value;
      unsigned long conversaionId_size;
      my_bool conversaionId_null;

      // content_
      //
      details::buffer content_value;
      unsigned long content_size;
      my_bool content_null;

      // time_
      //
      long long time_value;
      my_bool time_null;

      // seq_
      //
      long long seq_value;
      my_bool seq_null;

      // platform_
      //
      int platform_value;
      my_bool platform_null;

      // msgType_
      //
      int msgType_value;
      my_bool msgType_null;

      // groupId_
      //
      details::buffer groupId_value;
      unsigned long groupId_size;
      my_bool groupId_null;

      std::size_t version;
    };

    struct extra_statement_cache_type;

    using object_traits<object_type>::id;

    static id_type
    id (const id_image_type&);

    static id_type
    id (const image_type&);

    static bool
    grow (image_type&,
          my_bool*);

    static void
    bind (MYSQL_BIND*,
          image_type&,
          mysql::statement_kind);

    static void
    bind (MYSQL_BIND*, id_image_type&);

    static bool
    init (image_type&,
          const object_type&,
          mysql::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    static void
    init (id_image_type&, const id_type&);

    typedef mysql::object_statements<object_type> statements_type;

    typedef mysql::query_base query_base_type;

    static const std::size_t column_count = 10UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, object_type&);

    static pointer_type
    find (database&, const id_type&);

    static bool
    find (database&, const id_type&, object_type&);

    static bool
    reload (database&, object_type&);

    static void
    update (database&, const object_type&);

    static void
    erase (database&, const id_type&);

    static void
    erase (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    public:
    static bool
    find_ (statements_type&,
           const id_type*);

    static void
    load_ (statements_type&,
           object_type&,
           bool reload);
  };

  template <>
  class access::object_traits_impl< ::ChatLog, id_common >:
    public access::object_traits_impl< ::ChatLog, id_mysql >
  {
  };

  // ChatLog
  //
}

#include "chatlog-odb.ixx"

#include <odb/post.hxx>

#endif // CHATLOG_ODB_HXX
