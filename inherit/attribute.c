// 角色属性接口ATTRIBUTE
#include <dbase.h>

// 设置属性值
int set_attr(string attr, int value)
{
    return set("attr/" + attr, value);
}
int set_attrs(int hp, int mp, int str, int vit, int agi){
    set("attr/hp", hp);
    set("attr/mp", mp);
    set("attr/str", str);
    set("attr/vit", vit);
    set("attr/agi", agi);
    return 1;
}

// 更新属性值
int add_attr(string attr, int value)
{
    return add("attr/" + attr, value);
}
// 获取属性值
int query_attr(string attr)
{
    return query("attr/" + attr);
}

// 力量
int query_str()
{
    return query_attr("str");
}
// 敏捷
int query_agi()
{
    return query_attr("agi");
}
// 体格
int query_vit()
{
    return query_attr("vit");
}
// 智力
int query_int()
{
    return query_attr("int");
}
// 灵巧
int query_dex()
{
    return query_attr("dex");
}
// 幸运
int query_luk()
{
    return query_attr("luk");
}

// 最大HP
int query_max_hp()
{
    return query_attr("max_hp") + query_vit() * 10;
}
// 最大MP
int query_max_mp()
{
    return query_attr("max_mp") + query_int() * 5;
}
// 当前HP
int query_hp()
{
    return query_attr("hp");
}
// 当前MP
int query_mp()
{
    return query_attr("mp");
}

// 攻击
int query_attack()
{
    return query_str() * 8 + query_luk() / 5;
}
// 防御
int query_defense()
{
    return query_vit() * 2;
}
// 法术攻击
int query_m_attack()
{
    return query_int() * 6 + query_luk() / 5;
}
// 法术防御
int query_m_defense()
{
    return query_int() / 2;
}
// 体力恢复力
int query_hp_mend()
{
    return query_vit() / 5;
}
// 灵力恢复力
int query_mp_mend()
{
    return query_int() / 3;
}
//恢复力
int query_mend()
{
    return query_hp_mend() + query_mp_mend();
}

// 恢复
int set_hp_full() { return set_attr("hp", query_max_hp()); }
int set_mp_full() { return set_attr("mp", query_max_mp()); }
void set_all_full()
{
    set_hp_full();
    set_mp_full();
}
// 清零(die)
int set_hp_zero() { return set_attr("hp", 0); }
int set_mp_zero() { return set_attr("mp", 0); }
void set_all_zero()
{
    set_hp_zero();
    set_mp_zero();
}
// 判断
int is_hp_full() { return query_hp() >= query_max_hp(); }
int is_mp_full() { return query_mp() >= query_max_mp(); }
int is_all_full()
{
    return is_hp_full() && is_mp_full();
}

//demage
nosave string *dead_msg = ({
    "$ME慢慢倒在地上，身体化为一道流光消失了。",
    "$ME无力的挣扎几下后，化做泡影消失在大家眼前。",
});

nosave object last_damage_from = 0;

object query_last_damage_from()
{
    return last_damage_from;
}

// damage 为负时为恢复
varargs int receive_damage(string type, int damage, object who)
{
    int val, max;

    if (type != "hp" && type != "mp")
        error("receive_damage: 伤害种类错误(只能是 hp 或 mp)。\n");

    if (damage == 0)
        return 0;

    if (damage > 0 && objectp(who) && who != last_damage_from)
    {
        last_damage_from = who;
    }

    val = (int)query_attr(type) - damage;
    max = (type == "hp") ? query_max_hp() : query_max_mp();

    if (val >= max) // 恢复不超过最大值
        set_attr(type, max);
    else
        set_attr(type, val);

    return damage;
}

varargs void die(object killer)
{
    object me;
    string rebornroom;
    me = this_object();

    if (!killer)
    {
        killer = last_damage_from;
    }

    msg("vision", element_of(dead_msg), me);

    if (userp(me))
    {
        // 清除临时状态
        me->delete_temp("status");
        // 清除增益状态
        me->clean_condition();
        // todo 新增虚弱效果

        if (!stringp(rebornroom = me->query("reborn_room")) ||
            file_size(rebornroom + ".c") < 0)
            rebornroom = START_ROOM;
        me->move(rebornroom);
        me->start_busy(3);
        me->save();
    }
    else
    {
        set_heart_beat(0);
        destruct(me);
    }
}