package com.example.greenhousemonitoringcontrolsystem.db;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.util.Log;

import androidx.annotation.Nullable;

import com.example.greenhousemonitoringcontrolsystem.utils.TimeCycle;

import java.util.ArrayList;
import java.util.List;

public class DBDao implements DaoBase {
    private Context context;
    private DBHelper helper;
    private SQLiteDatabase db;
    private String TAG = "DBDao";

    public DBDao(Context context) {
        this.context = context;
        helper = new DBHelper(context);
    }

    @Override
    public int insert(Object object) {
        try {
            if (object instanceof DBData) {
                DBData data = (DBData) object;
                db = helper.getWritableDatabase();
                ContentValues values = new ContentValues();
                values.put("temp", data.getTemp());
                values.put("humi", data.getHumi());
                values.put("light", data.getLight());
                values.put("trhumi", data.getTrhumi());
                values.put("createDateTime", TimeCycle.getDateTime());
                db.insert("my", null, values);
                db.close();
                return 1;
            } else {
                return 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, "添加数据库错误");
            return -1;
        }
    }

    @Override
    public int delete(String... data) {
        return 0;
    }

    @Override
    public int update(Object object, String... data) {
        return 0;
    }

    @Override
    public List<Object> query(@Nullable String... data) {
        try {
            db = helper.getReadableDatabase();
            Cursor cursor;
            String sql;
            List<Object> result = new ArrayList<Object>();
            switch (data.length) {
                case 2:
                    sql = "SELECT * FROM my where datetime(createDateTime) " +
                            "BETWEEN datetime(?) AND datetime(?) ORDER BY createDateTime DESC;";
                    cursor = db.rawQuery(sql, data);
                    break;
                default:
                    sql = "SELECT * FROM my ORDER BY createDateTime DESC;";
                    cursor = db.rawQuery(sql, null);
            }
            while (cursor.moveToNext()) {
                DBData temp = new DBData();
                temp.setTrhumi(cursor.getString(cursor.getColumnIndexOrThrow("trhumi")));
                temp.setLight(cursor.getString(cursor.getColumnIndexOrThrow("light")));
                temp.setHumi(cursor.getString(cursor.getColumnIndexOrThrow("humi")));
                temp.setTemp(cursor.getString(cursor.getColumnIndexOrThrow("temp")));
                temp.setCreateDateTime(cursor.getString(cursor.getColumnIndexOrThrow("createDateTime")));
                result.add(temp);
            }
            cursor.close();
            db.close();
            return result;
        } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, "查询数据库失败");
            return null;
        }
    }
}
