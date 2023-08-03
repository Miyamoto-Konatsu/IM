// -*- C++ -*-
//
// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

namespace odb
{
  // Conversation
  //

  inline
  access::object_traits< ::Conversation >::id_type
  access::object_traits< ::Conversation >::
  id (const object_type& o)
  {
    return o.conversationKey_;
  }

  inline
  void access::object_traits< ::Conversation >::
  callback (database& db, object_type& x, callback_event e)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (x);
    ODB_POTENTIALLY_UNUSED (e);
  }

  inline
  void access::object_traits< ::Conversation >::
  callback (database& db, const object_type& x, callback_event e)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (x);
    ODB_POTENTIALLY_UNUSED (e);
  }
}

namespace odb
{
  // ConversationKey
  //

  inline
  bool access::composite_value_traits< ::ConversationKey, id_mysql >::
  get_null (const image_type& i)
  {
    bool r (true);
    r = r && i.ownerId_null;
    r = r && i.conversationId_null;
    return r;
  }

  inline
  void access::composite_value_traits< ::ConversationKey, id_mysql >::
  set_null (image_type& i,
            mysql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace mysql;

    i.ownerId_null = 1;
    i.conversationId_null = 1;
  }

  // Conversation
  //

  inline
  void access::object_traits_impl< ::Conversation, id_mysql >::
  erase (database& db, const object_type& obj)
  {
    callback (db, obj, callback_event::pre_erase);
    erase (db, id (obj));
    callback (db, obj, callback_event::post_erase);
  }

  inline
  void access::object_traits_impl< ::Conversation, id_mysql >::
  load_ (statements_type& sts,
         object_type& obj,
         bool)
  {
    ODB_POTENTIALLY_UNUSED (sts);
    ODB_POTENTIALLY_UNUSED (obj);
  }
}
