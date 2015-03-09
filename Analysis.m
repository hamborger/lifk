%% Data analysis for NetworkSim2.m output

% Reading 
listing = dir('*.dat');
nGroups = 10;
nN = 100;
l_lst = length(listing);
size(listing)
for q=1:l_lst
    m = csvread(listing(q).name);
    spikes = m(:,2+2*nGroups*nN:201+2*nGroups*nN);
  
    %PSTH
    %figure;
    psth = zeros(nGroups,iters);
    for g = 1:nGroups
    %    subplot(nGroups,1,g);
        psth(:,g) = sum(:,spikes((g-1)*nN+1:g*nN));
    %    plot(psth(g,:));
        [i,j,k]=find(psth(:,g)>=1);
        va(g)=var(psth(i(1):i(length(i)),g));
        mn(g)=mean(psth(i(1):i(length(i)),g));
    end
    %print('-dpng',sprintf('PSTH %s.png',listing(q).name));
    %close();
    
    %fano factor calculation
    ff=va./mn;
    figure;
    title('Activity phase plane')
    xlabel('sigma')
    ylabel('alpha')
    plot(sqrt(va),mn);
    print('-dpng',sprintf('alpha vs sigma %s.png',listing(q).name));
    close();
end



    
