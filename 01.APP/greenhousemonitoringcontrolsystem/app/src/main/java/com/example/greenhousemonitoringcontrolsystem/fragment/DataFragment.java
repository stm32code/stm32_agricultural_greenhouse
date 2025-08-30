package com.example.greenhousemonitoringcontrolsystem.fragment;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.example.greenhousemonitoringcontrolsystem.R;
import com.example.greenhousemonitoringcontrolsystem.bean.Receive;
import com.example.greenhousemonitoringcontrolsystem.db.DBData;
import com.example.greenhousemonitoringcontrolsystem.utils.Common;
import com.suke.widget.SwitchButton;
import com.youth.banner.Banner;
import com.youth.banner.adapter.BannerImageAdapter;
import com.youth.banner.holder.BannerImageHolder;
import com.youth.banner.indicator.CircleIndicator;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.ArrayList;
import java.util.List;


public class DataFragment extends Fragment {
    private Banner banner;
    private TextView messageText, tempText, humiText, lightText, trHumiText, tempSeekBarText, lightSeekBarText, humiSeekBarText, trHumiSeekBarText;
    private SeekBar tempSeekBar, humiSeekBar, lightSeekBar, trHumiSeekBar;
    private ImageView waterSwitch, manualSwitch, autoSwitch;


    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EventBus.getDefault().register(this);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_data, container, false);
        initView(view);
        return view;
    }

    /***
     * 初始化视图
     * @param view
     */
    private void initView(@NonNull View view) {
        bindingView(view);
        bannerConfig();
        eventConfig();
    }

    /**
     * 绑定控件
     *
     * @param view
     */
    private void bindingView(@NonNull View view) {
        banner = view.findViewById(R.id.bannerView);
        messageText = view.findViewById(R.id.messageText);
        tempText = view.findViewById(R.id.tempText);
        humiText = view.findViewById(R.id.humiText);
        lightText = view.findViewById(R.id.lightText);
        trHumiText = view.findViewById(R.id.trHumiText);
        tempSeekBar = view.findViewById(R.id.tempSeekBar);
        humiSeekBar = view.findViewById(R.id.humiSeekBar);
        lightSeekBar = view.findViewById(R.id.lightSeekBar);
        trHumiSeekBar = view.findViewById(R.id.trHumiSeekBar);
        tempSeekBarText = view.findViewById(R.id.tempSeekBarText);
        humiSeekBarText = view.findViewById(R.id.humiSeekBarText);
        lightSeekBarText = view.findViewById(R.id.lightSeekBarText);
        trHumiSeekBarText = view.findViewById(R.id.trHumiSeekBarText);
        waterSwitch = view.findViewById(R.id.waterSwitch);
        manualSwitch = view.findViewById(R.id.manualSwitch);
        autoSwitch = view.findViewById(R.id.autoSwitch);
    }

    /***
     * 轮播图配置
     */
    private void bannerConfig() {
        List<Integer> id = new ArrayList<Integer>();
        id.add(R.mipmap.i1);
        id.add(R.mipmap.i2);
        id.add(R.mipmap.i3);
        banner.setAdapter(new BannerImageAdapter<Integer>(id) {
            @Override
            public void onBindView(BannerImageHolder holder, Integer data, int position, int size) {
                holder.imageView.setImageResource(data);
            }
        });
        banner.isAutoLoop(true);
        banner.setIndicator(new CircleIndicator(getContext()));
        banner.start();
    }

    /***
     * 控件监听
     */
    private void eventConfig() {
        waterSwitch.setOnClickListener(view -> {
            waterSwitch.setSelected(!waterSwitch.isSelected());
            Common.SocketSend(2, waterSwitch.isSelected() ? "1" : "0");
        });
        manualSwitch.setOnClickListener(view -> {
            manualSwitch.setSelected(!manualSwitch.isSelected());
            autoSwitch.setSelected(!manualSwitch.isSelected());
            messageText.setText(manualSwitch.isSelected() ? "手动模式已开启" : "自动模式已开启");
            Common.SocketSend(1, autoSwitch.isSelected() ? "0" : "1");
        });
        autoSwitch.setOnClickListener(view -> {
            autoSwitch.setSelected(!autoSwitch.isSelected());
            manualSwitch.setSelected(!autoSwitch.isSelected());
            messageText.setText(autoSwitch.isSelected() ? "自动模式已开启" : "手动模式已开启");
            Common.SocketSend(1, autoSwitch.isSelected() ? "0" : "1");
        });
        trHumiSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                trHumiSeekBarText.setText(String.valueOf(i));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                trHumiSeekBarText.setText(String.valueOf(seekBar.getProgress()));
                Common.SocketSend(3, tempSeekBarText.getText().toString(), humiSeekBarText.getText().toString(), trHumiSeekBarText.getText().toString(), lightSeekBarText.getText().toString());
            }
        });
        humiSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                humiSeekBarText.setText(String.valueOf(i));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                humiSeekBarText.setText(String.valueOf(seekBar.getProgress()));
                Common.SocketSend(3, tempSeekBarText.getText().toString(), humiSeekBarText.getText().toString(), trHumiSeekBarText.getText().toString(), lightSeekBarText.getText().toString());
            }
        });

        lightSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                lightSeekBarText.setText(String.valueOf(i));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                lightSeekBarText.setText(String.valueOf(seekBar.getProgress()));
                Common.SocketSend(3, tempSeekBarText.getText().toString(), humiSeekBarText.getText().toString(), trHumiSeekBarText.getText().toString(), lightSeekBarText.getText().toString());
            }
        });

        tempSeekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                tempSeekBarText.setText(String.valueOf(i));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                tempSeekBarText.setText(String.valueOf(seekBar.getProgress()));
                Common.SocketSend(3, tempSeekBarText.getText().toString(), humiSeekBarText.getText().toString(), trHumiSeekBarText.getText().toString(), lightSeekBarText.getText().toString());
            }
        });
    }

    /**
     * 解析数据
     *
     * @param result
     */
    @Subscribe(threadMode = ThreadMode.MAIN)
    public void receiveDataFormat(Receive result) {
        try {
            if (result.getHumi() != null) {
                humiText.setText(result.getHumi());
            }
            if (result.getTemp() != null) {
                tempText.setText(result.getTemp());
            }
            if (result.getLight() != null) {
                lightText.setText(result.getLight());
            }
            if (result.getSoil_humi() != null) {
                trHumiText.setText(result.getSoil_humi());
            }
            if (result.getHumi_v() != null) {
                humiSeekBar.setProgress(Integer.parseInt(result.getHumi_v()));
                humiSeekBarText.setText(String.valueOf(humiSeekBar.getProgress()));
            }
            if (result.getTemp_v() != null) {
                tempSeekBar.setProgress(Integer.parseInt(result.getTemp_v()));
                tempSeekBarText.setText(String.valueOf(tempSeekBar.getProgress()));
            }
            if (result.getLight_v() != null) {
                lightSeekBar.setProgress(Integer.parseInt(result.getLight_v()));
                lightSeekBarText.setText(String.valueOf(lightSeekBar.getProgress()));
            }
            if (result.getSoil_humi_v() != null) {
                trHumiSeekBar.setProgress(Integer.parseInt(result.getSoil_humi_v()));
                trHumiSeekBarText.setText(String.valueOf(trHumiSeekBar.getProgress()));
            }

            if (result.getPump() != null) {
                waterSwitch.setSelected(result.getPump().equals("1"));
            }
//            if (result.getLed() != null) {
////                humiText.setText(result.getHumi());
//            }
            if (result.getFlage() != null) {
                manualSwitch.setSelected(result.getFlage().equals("1"));
                autoSwitch.setSelected(!result.getFlage().equals("1"));
                messageText.setText(autoSwitch.isSelected() ? "自动模式已开启" : "手动模式已开启");
            }


        } catch (Exception e) {
            e.printStackTrace();
            Toast.makeText(getContext(), "数据解析失败", Toast.LENGTH_SHORT).show();
        }
    }


    @Override
    public void onDestroy() {
        super.onDestroy();
        EventBus.getDefault().unregister(this);
    }
}