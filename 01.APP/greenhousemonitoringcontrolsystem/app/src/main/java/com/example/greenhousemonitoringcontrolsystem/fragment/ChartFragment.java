package com.example.greenhousemonitoringcontrolsystem.fragment;

import static com.example.greenhousemonitoringcontrolsystem.utils.TimeCycle.compareDateTime;

import android.app.DatePickerDialog;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.DatePicker;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.greenhousemonitoringcontrolsystem.R;
import com.example.greenhousemonitoringcontrolsystem.adapter.RecyclerViewAdapter;
import com.example.greenhousemonitoringcontrolsystem.chart.CreationChart;
import com.example.greenhousemonitoringcontrolsystem.db.DBDao;
import com.example.greenhousemonitoringcontrolsystem.db.DBData;
import com.github.mikephil.charting.charts.LineChart;

import java.util.Calendar;
import java.util.List;


public class ChartFragment extends Fragment {

    private RecyclerView recyclerView;
    private DBDao dao;
    private List<Object> objects;
    private RecyclerViewAdapter adapter;
    private TextView startTimeBtn, endTimeBtn;
    private ImageView searchBtn;
    private LineChart chart;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_chart, container, false);
        dao = new DBDao(getContext());
        objects = dao.query();
        initView(view);
        return view;
    }

    /***
     * 初始化视图
     * @param view
     */
    private void initView(@NonNull View view) {
        bindingView(view);
        eventConfig();
    }

    private void bindingView(View view) {
        recyclerView = view.findViewById(R.id.recyclerView);
        startTimeBtn = view.findViewById(R.id.startDateTime);
        endTimeBtn = view.findViewById(R.id.endDateTime);
        searchBtn = view.findViewById(R.id.searchBtn);
        chart = view.findViewById(R.id.chartView);
        CreationChart.initChart(chart);
        listViewConfig(objects);
    }

    private void listViewConfig(List<Object> objects) {
        for (Object object : objects) {
            DBData d = (DBData) object;
            CreationChart.addEntry(chart,d);
        }
        adapter = new RecyclerViewAdapter(objects);
        LinearLayoutManager layoutManager = new LinearLayoutManager(getContext());
        layoutManager.setOrientation(LinearLayoutManager.VERTICAL);
        recyclerView.setAdapter(adapter);
        recyclerView.setLayoutManager(layoutManager);
    }

    private void eventConfig() {
        startTimeBtn.setOnClickListener(view -> {
            showDateTimeDialog(startTimeBtn, true);
        });
        endTimeBtn.setOnClickListener(view -> {
            showDateTimeDialog(endTimeBtn, true);
        });

        searchBtn.setOnClickListener(view -> {
            if (!startTimeBtn.getText().toString().equals("开始时间") && !endTimeBtn.getText().equals("结束时间")) {
                if (compareDateTime(endTimeBtn.getText().toString() + " 23:59:59", startTimeBtn.getText().toString() + " 00:00:00") > 0) {
                    objects = dao.query(startTimeBtn.getText().toString() + " 00:00:00", endTimeBtn.getText().toString() + " 23:59:59");
                    listViewConfig(objects);
                } else {
                    Toast.makeText(getContext(), "结束时间必须大于开始时间", Toast.LENGTH_SHORT).show();
                }
            } else {
                Toast.makeText(getContext(), "请先设置时间", Toast.LENGTH_SHORT).show();
            }
        });
    }

    /**
     * 显示日期弹窗
     *
     * @param view   TextView
     * @param setMax 是否设置日期最大值为当前
     */
    private void showDateTimeDialog(TextView view, boolean setMax) {
        //获取当前系统时间
        Calendar currentTime = Calendar.getInstance();
        DatePickerDialog datePickerDialog = new DatePickerDialog(getContext(), (x_, year, month, day) -> view.setText(String.format("%4d-%02d-%02d", year, month + 1, day)), currentTime.get(Calendar.YEAR), currentTime.get(Calendar.MONTH), currentTime.get(Calendar.DAY_OF_MONTH));
        if (setMax) {
            // 设置最大日期值为当前日期
            datePickerDialog.getDatePicker().setMaxDate(currentTime.getTimeInMillis());
        }
        datePickerDialog.show();
    }
}