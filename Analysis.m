%% Data analysis for NetworkSim2.m output

% Reading 
listing = dir('*.dat');
nGroups = 10;
nN = 100;
l_lst = length(listing);
size(listing)
for q=1:l_lst
    m = csvread(listing(q).name);
    spikes = m(:,2+2*nGroups*nN:(nGroups*nN+1)+2*nGroups*nN)>=-55.0;
    %PSTH
    %figure;
    psth = zeros(length(spikes(:,1)),nGroups);
    for g = 1:nGroups
        subplot(nGroups,1,g);
        %imagesc(sum(spikes(:,(g-1)*nN+1:g*nN)'))
        psth(:,g) = sum(spikes(:,(g-1)*nN+1:g*nN)');
        plot(psth(:,g));
        [i,j,k]=find(psth(:,g)>=1);
        if numel(i)~=0
            va(g)=var(psth(i(1):i(length(i)),g));
            mn(g)=mean(psth(i(1):i(length(i)),g));
        else
            va(g) = 0;
            mn(g) = 0;
        end
    end
    print('-dpng',sprintf('PSTH %s.png',listing(q).name));
    close();
    
    %fano factor calculation
    ff=va./mn;
    figure;
    title('Activity phase plane')
    xlabel('groups')
    ylabel('sigma')
    plot(sqrt(va));
    print('-dpng',sprintf('sigma %s.png',listing(q).name));
    close();

    figure;
    title('Activity phase plane')
    xlabel('groups')
    ylabel('alpha')
    plot(mn);
    print('-dpng',sprintf('alpha %s.png',listing(q).name));
    close();

    figure;
    title('Raster')
    xlabel('time')
    ylabel('Groups')
    imagesc(spikes');
    print('-dpng',sprintf('raster %s.png',listing(q).name));
    close();
    
    figure;
    title('Current')
    xlabel('time')
    ylabel('I')
    imagesc(m(:,2+1*nGroups*nN:(nGroups*nN+1)+1*nGroups*nN)');
    print('-dpng',sprintf('current %s.png',listing(q).name));
    close();   
    
    figure;
    title('Activity phase plane')
    xlabel('sigma')
    ylabel('alpha')
    plot(sqrt(va),mn);
    print('-dpng',sprintf('alpha vs sigma %s.png',listing(q).name));
    close();
end



    
