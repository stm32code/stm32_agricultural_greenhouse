package com.example.greenhousemonitoringcontrolsystem.adapter;

import android.content.Context;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.lifecycle.Lifecycle;
import androidx.recyclerview.widget.RecyclerView;
import androidx.viewpager2.adapter.FragmentStateAdapter;

import com.example.greenhousemonitoringcontrolsystem.fragment.ChartFragment;
import com.example.greenhousemonitoringcontrolsystem.fragment.DataFragment;
import com.example.greenhousemonitoringcontrolsystem.fragment.MyFragment;

import java.util.ArrayList;
import java.util.List;

public class NavigationViewPagerAdapter extends FragmentStateAdapter {
    private List<Fragment> fragments = new ArrayList<>();

    public NavigationViewPagerAdapter(@NonNull FragmentManager fragmentManager, @NonNull Lifecycle lifecycle) {
        super(fragmentManager, lifecycle);
        fragments.add(new DataFragment());
        fragments.add(new ChartFragment());
//        fragments.add(new MyFragment());
    }

    @NonNull
    @Override
    public Fragment createFragment(int position) {
        return fragments.get(position);
    }

    @Override
    public int getItemCount() {
        return fragments.size();
    }
}
