//
// Created by O'Connell, Jared on 10/16/17.
//

#include "test_helpers.hh"
#include "DepthBlock.hh"

TEST(DepthBlock, DepthBlock_def_constr)
{
    DepthBlock db;
    ASSERT_EQ(db.rid(),0);
    ASSERT_EQ(db.start(),0);
    ASSERT_EQ(db.end(),0);
    ASSERT_EQ(db.dp(),bcf_int32_missing);
    ASSERT_EQ(db.gq(),bcf_int32_missing);
    ASSERT_EQ(db.dpf(),bcf_int32_missing);
}

TEST(DepthBlock, DepthBlock_constr)
{
    DepthBlock db(5,15,20,10,11,12,2);
    ASSERT_EQ(db.rid(),5);
    ASSERT_EQ(db.start(),15);
    ASSERT_EQ(db.end(),20);
    ASSERT_EQ(db.dp(),10);
    ASSERT_EQ(db.dpf(),11);
    ASSERT_EQ(db.gq(),12);
}

TEST(DepthBlock, DepthBlock_intersect1)
{
    DepthBlock db1(5,1,100,10,10,10,2);
    DepthBlock db2(5,50,60,5,5,5,2);
    DepthBlock inters(5,50,60,10,10,10,2);
    ASSERT_EQ(db1.Intersect(db2),inters);
}

TEST(DepthBlock, DepthBlock_intersect2)
{
    DepthBlock db1(5,1,100,10,10,10,2);
    int rid=5, start=40, end=80;
    DepthBlock inters(5,40,80,10,10,10,2);
    ASSERT_EQ(db1.Intersect(rid, start, end),inters);
}

TEST(DepthBlock, DepthBlock_intersect_size1)
{
    DepthBlock db1(5,1,100,10,10,10,2);
    DepthBlock db2(5,50,60,5,5,5,2);
    ASSERT_EQ(db1.IntersectSize(db2),11);

    DepthBlock db3(10,50,60,5,5,5,2);
    ASSERT_EQ(db1.IntersectSize(db3),0);
}


TEST(DepthBlock, DepthBlock_intersect_size2)
{
    DepthBlock db1(5,1,100,10,10,10,2);
    int rid=5, start=40, end=80;
    ASSERT_EQ(db1.IntersectSize(rid, start, end),41);
    rid = 11;
    ASSERT_EQ(db1.IntersectSize(rid, start, end),0);
}

TEST(DepthBlock, DepthBlock_size)
{
    DepthBlock db1(5,1,100,10,10,10,2);
    ASSERT_EQ(db1.size(),100);
}

TEST(DepthBlock, DepthBlock_set_missing)
{
    DepthBlock db(5,1,100,10,10,10,2);
    db.SetToMissing();
    ASSERT_EQ(db.dp(),bcf_int32_missing);
    ASSERT_EQ(db.gq(),bcf_int32_missing);
    ASSERT_EQ(db.dpf(),bcf_int32_missing);
}

TEST(DepthBlock, DepthBlock_set_zero)
{
    DepthBlock db(5,1,100,10,10,10,2);
    db.SetToZero();
    ASSERT_EQ(db.dp(),0);
    ASSERT_EQ(db.gq(),0);
    ASSERT_EQ(db.dpf(),0);
}


TEST(DepthBlock, DepthBlock_add1)
{
    DepthBlock db1(5,1,100,10,10,10,2);
    DepthBlock db2(5,101,200,20,20,20,2);
    db1.Add(db2);
    ASSERT_EQ(db1.rid(),5);
    ASSERT_EQ(db1.start(),1);
    ASSERT_EQ(db1.end(),200);
    ASSERT_EQ(db1.dp(),15);
    ASSERT_EQ(db1.dpf(),15);
    ASSERT_EQ(db1.gq(),15);
}

TEST(DepthBlock, DepthBlock_add2)
{
    DepthBlock db1(5,1,100,10,10,10,2);
    DepthBlock db2(5,101,150,20,20,20,2);
    db1.Add(db2);
    ASSERT_EQ(db1.rid(),5);
    ASSERT_EQ(db1.start(),1);
    ASSERT_EQ(db1.end(),150);
    ASSERT_EQ(db1.dp(),13);
    ASSERT_EQ(db1.dpf(),13);
    ASSERT_EQ(db1.gq(),13);
}
