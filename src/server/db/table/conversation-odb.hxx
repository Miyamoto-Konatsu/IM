// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef CONVERSATION_ODB_HXX
#define CONVERSATION_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 20475UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "conversation.h"

#include <memory>
#include <cstddef>

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
  // Conversation
  //
  template <>
  struct class_traits< ::Conversation >
  {
    static const class_kind kind = class_object;
  };

  template <>
  class access::object_traits< ::Conversation >
  {
    public:
    typedef ::Conversation object_type;
    typedef ::Conversation* pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef ::ConversationKey id_type;

    static const bool auto_id = false;

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
  // ConversationKey
  //
  template <>
  class access::composite_value_traits< ::ConversationKey, id_mysql >
  {
    public:
    typedef ::ConversationKey value_type;

    struct image_type
    {
      // ownerId_
      //
      details::buffer ownerId_value;
      unsigned long ownerId_size;
      my_bool ownerId_null;

      // conversationId_
      //
      details::buffer conversationId_value;
      unsigned long conversationId_size;
      my_bool conversationId_null;
    };

    static bool
    grow (image_type&,
          my_bool*);

    static void
    bind (MYSQL_BIND*,
          image_type&,
          mysql::statement_kind);

    static bool
    init (image_type&,
          const value_type&,
          mysql::statement_kind);

    static void
    init (value_type&,
          const image_type&,
          database*);

    static bool
    get_null (const image_type&);

    static void
    set_null (image_type&,
              mysql::statement_kind);

    static const std::size_t column_count = 2UL;
  };

  // Conversation
  //
  template <typename A>
  struct query_columns< ::Conversation, id_mysql, A >
  {
    // conversationKey
    //
    struct conversationKey_class_
    {
      conversationKey_class_ ()
      {
      }

      // ownerId
      //
      typedef
      mysql::query_column<
        mysql::value_traits<
          ::std::string,
          mysql::id_string >::query_type,
        mysql::id_string >
      ownerId_type_;

      static const ownerId_type_ ownerId;

      // conversationId
      //
      typedef
      mysql::query_column<
        mysql::value_traits<
          ::std::string,
          mysql::id_string >::query_type,
        mysql::id_string >
      conversationId_type_;

      static const conversationId_type_ conversationId;
    };

    static const conversationKey_class_ conversationKey;

    // conversationType
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::u_short,
        mysql::id_ushort >::query_type,
      mysql::id_ushort >
    conversationType_type_;

    static const conversationType_type_ conversationType;

    // groupId
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::std::string,
        mysql::id_string >::query_type,
      mysql::id_string >
    groupId_type_;

    static const groupId_type_ groupId;

    // toUserId
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::std::string,
        mysql::id_string >::query_type,
      mysql::id_string >
    toUserId_type_;

    static const toUserId_type_ toUserId;

    // maxSeq
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::uint64,
        mysql::id_ulonglong >::query_type,
      mysql::id_ulonglong >
    maxSeq_type_;

    static const maxSeq_type_ maxSeq;

    // minSeq
    //
    typedef
    mysql::query_column<
      mysql::value_traits<
        ::uint64,
        mysql::id_ulonglong >::query_type,
      mysql::id_ulonglong >
    minSeq_type_;

    static const minSeq_type_ minSeq;
  };

  template <typename A>
  const typename query_columns< ::Conversation, id_mysql, A >::conversationKey_class_::ownerId_type_
  query_columns< ::Conversation, id_mysql, A >::conversationKey_class_::
  ownerId (A::table_name, "`conversationKey_ownerId`", 0);

  template <typename A>
  const typename query_columns< ::Conversation, id_mysql, A >::conversationKey_class_::conversationId_type_
  query_columns< ::Conversation, id_mysql, A >::conversationKey_class_::
  conversationId (A::table_name, "`conversationKey_conversationId`", 0);

  template <typename A>
  const typename query_columns< ::Conversation, id_mysql, A >::conversationKey_class_
  query_columns< ::Conversation, id_mysql, A >::conversationKey;

  template <typename A>
  const typename query_columns< ::Conversation, id_mysql, A >::conversationType_type_
  query_columns< ::Conversation, id_mysql, A >::
  conversationType (A::table_name, "`conversationType`", 0);

  template <typename A>
  const typename query_columns< ::Conversation, id_mysql, A >::groupId_type_
  query_columns< ::Conversation, id_mysql, A >::
  groupId (A::table_name, "`groupId`", 0);

  template <typename A>
  const typename query_columns< ::Conversation, id_mysql, A >::toUserId_type_
  query_columns< ::Conversation, id_mysql, A >::
  toUserId (A::table_name, "`toUserId`", 0);

  template <typename A>
  const typename query_columns< ::Conversation, id_mysql, A >::maxSeq_type_
  query_columns< ::Conversation, id_mysql, A >::
  maxSeq (A::table_name, "`maxSeq`", 0);

  template <typename A>
  const typename query_columns< ::Conversation, id_mysql, A >::minSeq_type_
  query_columns< ::Conversation, id_mysql, A >::
  minSeq (A::table_name, "`minSeq`", 0);

  template <typename A>
  struct pointer_query_columns< ::Conversation, id_mysql, A >:
    query_columns< ::Conversation, id_mysql, A >
  {
  };

  template <>
  class access::object_traits_impl< ::Conversation, id_mysql >:
    public access::object_traits< ::Conversation >
  {
    public:
    struct id_image_type
    {
      composite_value_traits< ::ConversationKey, id_mysql >::image_type id_value;

      std::size_t version;
    };

    struct image_type
    {
      // conversationKey_
      //
      composite_value_traits< ::ConversationKey, id_mysql >::image_type conversationKey_value;

      // conversationType_
      //
      unsigned short conversationType_value;
      my_bool conversationType_null;

      // groupId_
      //
      details::buffer groupId_value;
      unsigned long groupId_size;
      my_bool groupId_null;

      // toUserId_
      //
      details::buffer toUserId_value;
      unsigned long toUserId_size;
      my_bool toUserId_null;

      // maxSeq_
      //
      unsigned long long maxSeq_value;
      my_bool maxSeq_null;

      // minSeq_
      //
      unsigned long long minSeq_value;
      my_bool minSeq_null;

      std::size_t version;
    };

    struct extra_statement_cache_type;

    using object_traits<object_type>::id;

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

    static const std::size_t column_count = 7UL;
    static const std::size_t id_column_count = 2UL;
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
    persist (database&, const object_type&);

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
  class access::object_traits_impl< ::Conversation, id_common >:
    public access::object_traits_impl< ::Conversation, id_mysql >
  {
  };

  // Conversation
  //
}

#include "conversation-odb.ixx"

#include <odb/post.hxx>

#endif // CONVERSATION_ODB_HXX